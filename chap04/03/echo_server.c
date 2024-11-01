#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[])
{		
	int serv_sock;
	int clnt_sock;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	
	char message[BUF_SIZE];
    int str_len;
	
	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	/* socket() : 소켓 생성*/
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // socket(IPv4, TCP, 0)
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr)); // 구조체 안에 메모리를 0으로 세팅함
	serv_addr.sin_family = AF_INET; // 주소 체계 (AF_INET: IPv4 인터넷 프로토콜에 적용하는 주소체계)
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 32비트(4바이트) IP주소 (INADDR_ANY: 0.0.0.0)
	serv_addr.sin_port = htons(atoi(argv[1])); // 16비트(2바이트) TCP/UDP PORT번호
	
	/* bind() : 소켓 주소할당 */
	// 아래는 형변환(캐스팅) 연산자 (struct sockaddr*)를 사용하여 
	// 구조체sockaddr_in의 serv_addr의 주소에 넣은 것임(&은 주소참조연산자)
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) // bind(파일디스크립터, IP_PORT_구조체, 사이즈)
		error_handling("bind() error");
	
	/* listen() : 연결요청 대기상태 */
    // serv_sock : 리스닝 소켓
	if(listen(serv_sock, 5) == -1) // 연결요청 대기 큐의 사이즈 (클라이언트의 연결요청을 5개까지 대기시킬 수 있다.)
		error_handling("listen() error");
		
	clnt_addr_size = sizeof(clnt_addr);

	for (int i = 0; i < 3; i++)
	{
		/* accept() : 연결허용 */
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

		// clnt_sock : 새로 만든 클라이언트 소켓 디스크립터 (연결 요청만 기다리고 받기 위한 소켓)
		if(clnt_sock == -1)
			error_handling("accept() error");
        else
            printf("Connected client %d \n", i+1); // 몇 번째 client가 연결되었는지
		

        /* 데이터 수신 */
		while ( (str_len = read(clnt_sock, message, BUF_SIZE)) != 0 )
        {
            /* 데이터 송신 */
            write(clnt_sock, message, str_len);
        }
        


		/* close() : 연결종료 */
		close(clnt_sock);
	}
	
	/* close() : 연결종료 */
	close(serv_sock);
	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
