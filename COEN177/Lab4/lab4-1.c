//Name: Hanna Albright
//Date: January 28, 2021
//Title: Lab4 - Developing multi-threaded applications
//Description: This code creates 20 threads and has them output a statement (with their supposed iteration number and thread ID) to the terminal before joining them all together. All 20 threads get 'returned' (on the terminal) in order but not processed by the cpu in order of iteration number.
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS]; //array for thread identifiers

int main() {
    static int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);//create threads and use &i as an input to the function go
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);//join threads after they are done
	    printf("Thread %d returned \n", i);
    }
    printf("Main thread done.\n");
}
void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());//print out their thread iteration and ID
    return (NULL);
}
