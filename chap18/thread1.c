#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // 쓰레드

void* thread_main(void *arg);
void* thread_main_2(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id, t_id_2;
    int thread_param = 5;

    // pthread_create(스레드ID 주소값, NULL 함수명, 넘길 파라미터 주소값);
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_create(&t_id_2, NULL, thread_main_2, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }
    
    for (int i = 0; i < 5; i++)
    {
        sleep(1);
        puts("running main");
    }
    
    sleep(5);
    puts("end of main");

    return 0;
}

void* thread_main(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로
    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        puts("running thread 1");
    }
    
    return NULL;
}

void* thread_main_2(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로
    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        puts("running thread 2");
    }
    
    return NULL;
}