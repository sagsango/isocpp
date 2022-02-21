#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#define THREAD_COUNT 10


void pthread_once_routine(void){
	
	pthread_t t_id = pthread_self();
	printf(" ======>>> pthread_once_routine(): t_id = %lu\n", (unsigned long) t_id);

}

void static_once_routine(void){

	pthread_t t_id = pthread_self();
	printf(" ======>>> static_once_routine(): t_id = %lu\n", (unsigned long) t_id);

}

void *thread_routine(void *args){

	pthread_t t_id = pthread_self();
	printf("thread_routine(): t_id = %lu\n", (unsigned long) t_id);

	pthread_once_t once_control = PTHREAD_ONCE_INIT;
	pthread_once( &once_control, &pthread_once_routine);

	static bool static_once_init = true;
	if( static_once_init ){
		static_once_routine();
		static_once_init = false;
	}

	return NULL;
}

int main(){

	pthread_t t[THREAD_COUNT];

	for(int i=0;i<THREAD_COUNT;++i){
		pthread_create(&t[i], NULL,  &thread_routine, NULL);
	}

	sleep(10);

	for(int i=0;i<THREAD_COUNT;++i){
		pthread_join(t[i], NULL);
	}

	return 0;
}


