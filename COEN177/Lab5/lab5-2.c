// Name: Hanna Albright
// Date: 02/12/21 
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables
// Description: This program creates 10 threads which takes their iteration number (0-9) into the function go. While in go, the mutex is locked and the thread outputs a message with its iteration number, sleeps, then unlocks the mutex.After each thread is done, the threads are joined and the mutex lock is destroyed.
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock;

void* go(void* arg) { 
  pthread_mutex_lock(&lock);//lock mutex
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1); 
  pthread_mutex_unlock(&lock);//unlock mutex
  return (NULL);
} 

int main() { 
pthread_mutex_init(&lock, NULL);//initialize mutex
static int i;
for (i = 0; i < NTHREADS; i++){//create threads that take i as a parameter into the function "go"
 pthread_create(&threads[i], NULL, go, (void *)(size_t)i);  
}
for (i = 0; i < NTHREADS; i++) {//join threads
   pthread_join(threads[i],NULL);
   printf("\t\t\t Thread %d returned \n", i);
}
printf("Main thread done.\n");
pthread_mutex_destroy(&lock);//destroy mutex
return 0; 
} 
