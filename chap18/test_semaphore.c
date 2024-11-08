#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // 쓰레드
#include <semaphore.h> // 세마포어

void* thread_main(void *arg);
void* thread_main_2(void *arg);
void* thread_main_3(void *arg);

static sem_t sem_one;
static sem_t sem_two;
static sem_t sem_thr;

int main(int argc, char *argv[])
{
    pthread_t t_id, t_id_2, t_id_3;
    int thread_param = 5;

    sem_init(&sem_one, 0, 1); // sem_init(주소값, 0, 세마포어 초기값 설정)
	sem_init(&sem_two, 0, 0);
    sem_init(&sem_thr, 0, 0);

    // pthread_create(스레드ID 주소값, NULL, 함수명, 넘길 파라미터 주소값);
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_create(&t_id_2, NULL, thread_main_2, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_create(&t_id_3, NULL, thread_main_3, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    sleep(6);
    puts("end of main");

    sem_destroy(&sem_one);
	sem_destroy(&sem_two);
    sem_destroy(&sem_thr);

    return 0;
}

void* thread_main(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로
    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        sem_wait(&sem_one); // - 감소
        puts("running thread 2");
        sem_post(&sem_two); // + 증가
    }
    
    return NULL;
}

void* thread_main_2(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로
    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        sem_wait(&sem_two); // - 감소
        puts("running thread 1");
        sem_post(&sem_thr); // + 증가
    }
    
    return NULL;
}

void* thread_main_3(void *arg) // 넘겨진 파라미터 주소값
{
    int cnt = *((int*)arg); // 캐스트연산해서 int로
    for (int i = 0; i < cnt; i++)
    {
        sleep(1);
        sem_wait(&sem_thr); // - 감소
        puts("running thread 3");
        sem_post(&sem_one); // + 증가
    }
    
    return NULL;
}