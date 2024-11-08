#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // 쓰레드

struct profile
{
    int age;
    double height;
};

void* thread_main(void *arg);
void* thread_main_2(void *arg);
void* thread_profile(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id, t_id_2, t_id_3;
    int thread_param = 5;

    struct profile student;
    student.age = 15;
    student.height = 173;

    // pthread_create(스레드ID 주소값, NULL, 함수명, 넘길 파라미터 주소값);
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_create(&t_id_2, NULL, thread_main_2, (void*)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    if(pthread_create(&t_id_3, NULL, thread_profile, (void*)&student) != 0) {
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

void* thread_profile(void *arg)
{
    /*
    학생의 나이는 15살이고, 키는 173.0입니다.
    */
    struct profile student = *((struct profile*)arg); // 구조체로 캐스팅
    printf("학생의 나이는 %d살이고, 키는 %.1lf입니다.\n", student.age, student.height);

    return NULL;
}