// Name: Hanna Albright 
//  Date: January 21, 2021
// Title: Lab3-Pthreads and inter-process Communication – Pipes
// Description: This program creates ten threads, has them output a hello statement with their ID and iteration number (held in the location of the variable i). Because the location of the iteration number is passed through and not the value, some iteration numbers may get overwritten before it can be outputted from the terminal (hence some iteration numbers are skipped and other are printed out more than once). After this, the threads are joined. 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10 //NTHREADS=10
pthread_t threads[NTHREADS];
int main() {
	int i;
	for (i=0; i<NTHREADS; i++){
		pthread_create(&threads[i], NULL, go, &i);//create 10 threads and pass the location of i into the function go for each thread
	} 
	for (i=0; i<NTHREADS; i++){
		printf("Thread %d returned\n", i);
		pthread_join(threads[i], NULL);//join threads 
   	}
	printf("Main thread done.\n"); 
	return 0;
}

void *go(void *arg) { 
	printf("Hello from thread %d with iteration %d \n", (int)pthread_self(), *(int *)arg);//prints out thread id and iteration number (which could be different than when the thread was created)
return 0;
}



