// Name: Hanna Albright 
// Date: 02/12/21
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables 
// Description: This program creates 5 producer and consumer threads, condition variables, and a mutex lock to solve the producer-consumer problem. Each producer thread goes into the producer function, locks the mutex, and if the buffer isn't full, creates two items and adds them into the buffer. After this, it signals that the buffer has its items using a condition variable and unlocks the mutex. If the buffer is full,it unlocks the mutex and waits until signaled by the condition variable. In the consumer function, the consumer thread locks the mutex and if the the buffer not empty it takes in the item from the buffer, signals this using the condition variable, and unlocks the mutex. If the buffer is empty, it unlocks the mutex until signaled that by the condition variable from the producer function.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define N 10 
#define maxItem 2

pthread_mutex_t mutex;
int buffer[N];
int in, out;
pthread_cond_t cond1, cond2;//condition variables

void* producer(void* arg){
	int i,item;
	i=0;
	while(i<maxItem){
		item=rand()%10+1; //produce item
		pthread_mutex_lock(&mutex);//lock critical section
		while((in-out)==N){ //while buffer is full (Has unconsumed items in it)
			pthread_cond_wait(&cond1,&mutex);//unlocks mutex based on condition variable
		}
		buffer[in-out]=item;//insert item into buffer
		in= (in + 1) % N;
		i++;
		printf("Producer %d inserted item: %d\n", *(int*)arg, item);
		pthread_cond_signal(&cond2); //signal the buffer is full
		pthread_mutex_unlock(&mutex);//unlock mutex
	}
	pthread_exit(0);
	return(NULL);
}

void* consumer (void* arg){
	int k,item;
	k=0;
        while(k<maxItem){ //all items are greater than 1
		pthread_mutex_lock(&mutex);//lock critical section
		while(in==out){ //while the buffer is empty (Has no new items in it)
			pthread_cond_wait(&cond2,&mutex);//unlocks mutex based on condition variable
		}
		out= (out + 1) % N;
		item=buffer[in-out];
		k++;
		printf("Consumer %d Removed item: %d\n", *(int*)arg, item);
		pthread_cond_signal(&cond1);//signal buffer is empty
                pthread_mutex_unlock(&mutex);//unlock mutex
	}
	pthread_exit(0);
	return(NULL);
}

int main(){
	int i;
	in=0;
	out=0;
	pthread_t produce[5], consume[5];
	pthread_mutex_init(&mutex,NULL);//initialize mutex
	pthread_cond_init(&cond1,0);//initialize condition variables
        pthread_cond_init(&cond2,0);
	for (i=0;i<5;i++){//create 5 producer and consumer threads
		pthread_create(&produce[i],NULL,producer,produce+i);
        	pthread_create(&consume[i],NULL,consumer,consume+i);
	}
	for (i=0;i<5;i++){
		pthread_join(produce[i],NULL);//join threads
	}
	for (i=0;i<5;i++){
		pthread_join(consume[i],NULL);
	}
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_mutex_destroy(&mutex);
	return 0;
}
