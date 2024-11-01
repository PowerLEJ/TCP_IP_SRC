#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{		
	char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    // 인자로 in_addr 구조체 변수의 주소값을 전달하면, 변환된 값이 자동으로 in_addr 구조체 변수에 저장됨
    if(!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error!");
    else
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
