/*
    Simple udp server
    Silver Moon (m00n.silv3r@gmail.com)
*/

#include "wifi.h"

#define PORT 8888   //The port on which to listen for incoming data

struct sockaddr_in si_me, si_other;
int s, i, slen = sizeof(si_other);

void wifiInit()
{
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        perror("bind");
        exit(1);
    }
}

void wifiRX(char* RXData, int bytes_to_receive)
{
    int recv_len;

    if ((recv_len = recvfrom(s, RXData, bytes_to_receive, 0, (struct sockaddr *) &si_other, &slen)) == -1)
    {
        perror("recvfrom()");
        exit(1);
    }
}

void wifiTX(char* TXData, int bytes_to_send)
{
    int sent_len;

    if ( (sent_len = sendto(s, TXData, bytes_to_send, 0, (struct sockaddr *) &si_other, slen)) == -1)
    {
        perror("sendto()");
        exit(1);
    }
}

void wifiTerminate()
{
    close(s);
}
