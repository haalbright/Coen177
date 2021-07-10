//Name: Hanna Albright
//Date: 01/14/21
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: This program creates two threads that executes their own individual functions that print out a statement and their thread id.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void *firstthread(){
	printf("Thread 1 created with thread id: %d\n", (int)pthread_self()); //prints out first thread id
}

void *secondthread(){
        printf("Thread 2 created with thread id: %d\n", (int)pthread_self()); //prints out second thread id
}

int main(int argc, char *argv[]){
	pthread_t first, second;
	int err1, err2;
	err1 = pthread_create(&first, NULL, firstthread, NULL);//creates thread called first that will execute the function called firstthread
	if(err1){
		printf("Error creating thread 1 \n", errno);
	}
	err2 = pthread_create(&second, NULL, secondthread, NULL);//creates thread called second that will execute the function called secondthread
	if(err2){
                printf("Error creating thread 2 \n", errno);
        }
	pthread_join(first, NULL);//terminate first thread
	pthread_join(second, NULL);//terminate second thread
	return 0;
}

	
