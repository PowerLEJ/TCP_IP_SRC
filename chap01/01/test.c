// ./test 127.0.0.1 9190

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    struct sockaddr ip_port;

    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    printf("IP = %s\n", argv[1]);
    printf("PORT = %s\n", argv[2]);


    // 9190 숫자로 변경(4bype가 됨) 한 후 2byte로 바꾸기(unit16_t 사용)
    uint16_t port = (uint16_t)atoi(argv[2]);
    ip_port.sa_data[0] = (char)(port & 0x00FF); // 하위비트
    ip_port.sa_data[1] = (char)(port >> 8); // 상위비트

    // 포인터 방식
    // char *p = &port;
    // ip_port.sa_data[0] = *(p + 0);
    // ip_port.sa_data[1] = *(p + 1);

    printf("%x %x\n", ip_port.sa_data[0], ip_port.sa_data[1]);

    return 0;
}