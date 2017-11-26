#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

void wifiInit();
void wifiRX(char*,int);
void wifiTX(char*,int);
void wifiTerminate();

#endif
