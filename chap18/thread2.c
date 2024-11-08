#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // 쓰레드
#include <stdlib.h>
#include <string.h>

void* thread_main(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    void *thr_ret;

    // pthread_create(스레드ID 주소값, NULL, 함수명, 넘길 파라미터 주소값);
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    // pthread_join(해당 스레드ID가 종료될 때까지 함수는 반환하지 않는다, 
    //              스레드의 main 함수가 반환하는 값이 저장될 포인터 변수의 주소값)
    if(pthread_join(t_id, &thr_ret) != 0) {
        puts("pthread_join() error!");
        return -1;
    }

    printf("Thread return message : %s\n", (char*)thr_ret);
    
    free(thr_ret);

    return 0;
}

void* thread_main(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로

    char *msg = (char*)malloc(sizeof(char)*50);
    strcpy(msg, "Hello, I'm thread!\n");

    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        puts("running thread");
    }
    
    return (char*)msg;
}