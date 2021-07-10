// Name: Hanna Albright
// Date: 02/12/21 
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables
// Description: This program creates 10 threads which takes their iteration number (0-9) into the function go. There, it waits until the semaphore unlocks and then locks it and prints out its message and iteration number to the terminal and unlocks the semaphore. After each thread is done, the threads are joined and the semaphore is removed. 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex_2; 

void* go(void* arg) { 
  sem_wait(mutex_2); //wait until semaphore value becomes positive and decrement it
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section message
   sleep(1); 
  sem_post(mutex_2); //leave critical section and increment
  return (NULL);
} 

int main() { 
sem_unlink("mutex_2"); //ignore all past runs
mutex_2 = sem_open("mutex_2", O_CREAT, 0644, 1);//creates semaphore with 1 in the counter
static int i;
for (i = 0; i < NTHREADS; i++)  //create threads which take in i as a parameter to the function "go"
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {//join threads
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
sem_unlink("mutex_2");//remove semaphore 
return 0; 
} 
