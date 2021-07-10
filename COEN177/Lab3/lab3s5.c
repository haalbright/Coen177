//Time: Hanna Albright
//Date: January 21, 2021
//Title: Lab3-Pthreads and inter-process Communication – Pipes
//Description: This program creates a child and parent process through piping.  The child takes in a message (max of 60 characters) from the user and writes it upstream. The parent then reads it and writes the same message for the user to see.   

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
	int fds[2];// 2 files descriptors
	char buff[60];//buffer contain 60 char
	char message[60];
	int i,count;
	pipe(fds);//pipe system call
	if(fork()==0){//if child process
		close(fds[0]);//close downstream end
		printf("What is the message?");
		scanf("%59s",message);//get message from the user
		write(fds[1],message,60);//write message to upstream
		printf("\nMessage will print out below \n ");
		exit(0);
	}
	else if(fork()==0){//if parent
		close(fds[1]);//close upstream end
		wait(NULL);
		count=read(fds[0],buff,60);//read from downstream into buffer
		write(1, buff, count);//write from buffer
		printf("\n");
		exit(0);
	}
	else {
		close(fds[0]);//close both ends of the pipe
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
