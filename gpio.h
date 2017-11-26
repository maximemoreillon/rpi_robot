#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>
#include <softPwm.h>

void GPIOInit();
void motors(char*);
int servo();
int ultrasonic();
char TXPackaging(int, int);

#endif
