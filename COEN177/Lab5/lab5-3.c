// Name: Hanna Albright 
// Date: 02/12/21
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables 
// Description: This program creates 5 producer and consumer threads and semaphores to solve the producer-consumer problem. Each producer thread goes into the producer function,waits until the buffer is signaled to be empty and locks the semaphore, then creates and adds two items to the buffer. Then, it unlocks the semaphore and signals the buffer is full. In the consumer function, the consumer thread waits until the buffer is full and locks the semaphore. Then it takes in the item from the buffer, unlocks the semaphore and signals the buffer it empty. After all the items are consumed, the threads are joined together and the semaphores are destroyed.
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 10 
#define maxItem 2

sem_t empty, full, mutex;
int buffer[N];
int item;
int in, out;
void* producer(void* arg){
	int i;
	i=0;
	while(i<maxItem){
		item=rand()%10+1; //produce item
		sem_wait(&empty); //wait until buffer is empty
		sem_wait(&mutex);//lock critical section using the semaphore
		buffer[in]=item;//insert item into buffer
		in= (in + 1) % N;
		i++;
		printf("Producer %d inserted item: %d\n", *(int*)arg, item);
		sem_post(&mutex);//unlock critical section
		sem_post(&full);//signal buffer slots are full
	}
pthread_exit(0);
return(NULL);
}

void* consumer(void* arg){
	int k;
	k=0;
        while(k<maxItem){ //all items are greater than 1
		sem_wait(&full);//wait until buffer slots are full 
		sem_wait(&mutex);//lock critical section with semaphore
		item=buffer[out];//take out the item
		out= (out + 1) % N;
		k++;
		printf("Consumer %d Removed item: %d\n", *(int*)arg, item);
		sem_post(&mutex);//unlock critical section
		sem_post(&empty);//signal buffer slots are empty
	}
pthread_exit(0);
return(NULL);
}

int main(){
	int i;
	sem_destroy(&mutex);
        sem_destroy(&empty);
        sem_destroy(&full);
	in=0;
	out=0;
	sem_init(&empty,0,N);//initialize semaphores
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);
	pthread_t producers[5],consumers[5];//create threads
	for (i=0; i<5; i++){//create 5 producer and consumer threads
		pthread_create(&producers[i],NULL,producer,producers+i);
		pthread_create(&consumers[i],NULL,consumer,consumers+i);
	}
	for (i=0; i<5; i++){//join threads
		pthread_join(producers[i],NULL);
        }
	for (i=0; i<5; i++){
		pthread_join(consumers[i],NULL);       
	}
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
