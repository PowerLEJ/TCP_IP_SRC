#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD	100

void * thread_inc(void * arg);
void * thread_des(void * arg);
long long num=0; // long long형은 64비트 정수 자료형

pthread_mutex_t mutex; // 뮤텍스(Mutex) : 동일한 메모리 영역으로의 동시접근이 발생하는 상황 (ex.화장실)

int main(int argc, char *argv[]) 
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화

	printf("sizeof long long: %d \n", sizeof(long long));
	for(i=0; i<NUM_THREAD; i++)
	{
		if(i%2)
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);	
	}	

	for(i=0; i<NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL);

	printf("result: %lld \n", num);
	return 0;
}

void * thread_inc(void * arg) 
{
	int i;
	pthread_mutex_lock(&mutex); // 뮤텍스 락
	for(i=0; i<50000000; i++) {
		num+=1;
	}
	pthread_mutex_unlock(&mutex); // 뮤텍스 언락
	return NULL;
}
void * thread_des(void * arg)
{
	int i;
	for(i=0; i<50000000; i++) {
		pthread_mutex_lock(&mutex);
		num-=1;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}