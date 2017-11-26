#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);

#include "gpio.h"
#include "wifi.h"


int main(void)
{
    GPIOInit();
    wifiInit();
    
    printf("MES-ROBOT: Robot activated\n");
    
    while(1)
    {
        // receiving data for the motors
        char RXData[1];
        wifiRX(RXData,1);
	if(RXData[0]==0x00)
	{
		printf("terminating\n"); // exit program if byte 0x00 is received, leads to shutdown
		break;
	}

        motors(RXData); // Apply data to motors

        // reading sonar
        int angle = servo(); // setting angle to servo and teruning it
        int distance = ultrasonic(); // reading ultrasonic sensor

        // sending angle and distance data
        char TXData[1];
        TXData[0] = TXPackaging(angle, distance);
        wifiTX(TXData,1);
    }

    wifiTerminate();
    return 0;
}
