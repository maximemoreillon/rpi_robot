#include "gpio.h"

#define MotorR1 0
#define MotorR2 1
#define MotorL1 2
#define MotorL2 3

#define servoPin 4
#define trigPin 5
#define echoPin 6

int angle = 10;
int direction = 1;

void GPIOInit()
{
    // wiringPi library initialisation
    if(wiringPiSetup()==-1)
    {
        printf("GPIO Error\n");
        exit(1);
    }

    // setting pins
    softPwmCreate(MotorR1, 0, 100);
    softPwmCreate(MotorR2, 0, 100);
    softPwmCreate(MotorL1, 0, 100);
    softPwmCreate(MotorL2, 0, 100);
    softPwmCreate(servoPin, 10, 400);

    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);

    // ultrasonic trig pin must start low
    digitalWrite(trigPin, LOW);
}

void motors(char* command)
{
    int motorR = (int) (command[0]&0xf0)>>4;
    int motorL = (int) command[0]&0x0f;

    motorR = 200*motorR/15-100;
    motorL = 200*motorL/15-100;

    // dead zone
    if(abs(motorR)<10) motorR = 0;
    if(abs(motorL)<10) motorL = 0;

    if(motorR>=0)
    {
        softPwmWrite(MotorR1, motorR);
        softPwmWrite(MotorR2, 0);
    }
    else
    {
        softPwmWrite(MotorR1, 0);
        softPwmWrite(MotorR2, -motorR);
    }

    if(motorL>=0)
    {
        softPwmWrite(MotorL1, motorL);
        softPwmWrite(MotorL2, 0);
    }
    else
    {
        softPwmWrite(MotorL1, 0);
        softPwmWrite(MotorL2, -motorL);
    }
}

int servo()
{
    angle += direction;

    if(angle >= 19)
        direction = -1;

    if(angle <= 3)
        direction = 1;

    softPwmWrite(servoPin,angle);

    return angle;
}


int ultrasonic()
{
    // Send trig pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Wait for echo start
    long timeout = 50000;
    long startTime = micros(); // Used for timeout

    while(digitalRead(echoPin) == LOW) // Wait for ultrasonic sensor to be ready for echo
    {
	if(micros() - startTime > timeout) // If this fails, don't bother trying any harder, return a dummy value
	{
	    printf("Ultrasonic timeout 1\n");
	    return 51;
	}
    }

    // Wait for echo end
    startTime = micros(); // Used for timeout

    while(digitalRead(echoPin) == HIGH) // wait for echo
    {
	if(micros() - startTime > timeout) // but don't wait too much
	{
	    printf("Ultrasonic timeout 2\n");
	    break;
	}
    }

    long travelTime = micros() - startTime;

    // Get distance in cm
    int distance = travelTime / 58; // conversion between echo time and distance

    return distance;
}

char TXPackaging(int ang, int dist)
{
    // formatting angle
    char angleChar;

    if(ang >= 19 ||ang <= 3)
        angleChar = (char) 0;
    else
        angleChar = (char) (15.00*ang/20.00);

    angleChar = angleChar << 4;

    // formatting distance
    char distChar = (char) (15.00*dist/51.00);

    // output
    char out = angleChar | distChar;
    return out;
}
