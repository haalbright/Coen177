// Name: Hanna Albright
// Date: January 21, 2021
// Title: Lab3- Pthreads and inter-process Communication – Pipes
// Description: This program create 10 threads. Each thread outputs their ID and iteration number. After this, all the threads are joined together.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];//create 10 file descriptors
int main() {
	int index[NTHREADS];//array to fill with iteration numbers
  	int i;
  	for (i = 0; i < NTHREADS; i++) {
    		index[i] = i;//fill array with iteration numbers
    		pthread_create(&threads[i], NULL, go, index+i);//create threads which executes go function with input of index+i
  	}
  	for (i = 0; i < NTHREADS; i++) {
   		printf("Thread %d returned\n", i);
    	pthread_join(threads[i],NULL);//joins all threads
  	}
  	printf("Main thread done.\n");
  	return 0;
}

void *go(void *arg) {
	printf("Hello from thread %d with iteration %d\n",(int)pthread_self(),*(int *)arg);//message that prints out thread ID and iteration number
	return 0;
}

