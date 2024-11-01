#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port); // short형 host를 network로 (빅엔디안으로)
    net_addr = htonl(host_addr); // long형 host를 network로 (빅엔디안으로)

    printf("Host ordered port : %#x \n", host_port);
    printf("Network ordered port : %#x \n", net_port);
    printf("Host ordered address : %#x \n", host_addr);
    printf("Network ordered address : %#x \n", net_addr);

    return 0;
}