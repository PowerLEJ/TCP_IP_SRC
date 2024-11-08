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
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;
	
	if(argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	/* socket() : 소켓생성 */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");
	
	// 접속할 서버의 IP
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 문자열을 네트워크 바이트 순서의 정수로 변환
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	/* connect() : 연결요청 */
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");
	


    while (1)
    {
        fputs("Input message(Q to quit) : ", stdout); // 모니터에 출력
        fgets(message, BUF_SIZE, stdin); // 키보드에서 값을 읽어서 message에 1024만큼 써줘 (엔터 치면 종료)

        // q 또는 Q를 입력하면 반복문 종료
        if(strcmp(message, "q\n") == 0 || strcmp(message, "Q\n") == 0)
            break;

        /* write() 데이터 송신 */
        // str_len 총 보낸 갯수
        str_len = write(sock, message, strlen(message)); // message의 갯수만큼만 보내주기 위해 strlen 사용

        recv_len = 0; // 총 받은 message의 갯수
        while (recv_len < str_len)
        {
            // 몇 개를 읽었는지 리턴해서 recv_cnt에 넣어줌
            /* read() : 데이터 수신 */
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE-1); // 몇 개가 돌아올지 몰라서 (버퍼사이즈-1)로 설정함. 

            if(recv_cnt == -1)
                error_handling("read() error");
            recv_len += recv_cnt;
        }
        message[recv_len] = 0; // 메시지의 맨뒤값은 0으로 설정
        printf("Message from server: %s", message);
    }
    


	/* close() : 연결종료 */
	close(sock);
	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
