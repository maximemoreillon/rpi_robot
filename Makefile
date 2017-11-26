CC=gcc
CFLAGS=-O0 -lwiringPi -lpthread
all:
	$(CC) $(CFLAGS) main.c gpio.c wifi.c -o MES

clean:
	rm -rf MES *.o *~
