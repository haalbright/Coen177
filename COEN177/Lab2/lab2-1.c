//Name: Hanna Albright
//Date: 01/14/21
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: This program creates a fork and prints out the number 0-99 in the child and parent process. After a number is printed out, there is a delay of n microseconds where n is taken as an input from the user. If the fork fails, an error message will print showing the standard error message, "can't fork, error" message, and the error number.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
	printf("\n Before forking. \n");
	pid = fork();
	if (pid == -1){ //if system fails
		fprintf(stderr, "can't fork, error %d\n", errno); //prints standard error message and error number
		usleep(n); //delay for n microseconds
	}
	if (pid){ //if a pid is parent process id
		for (i=0;i<100;i++){
			printf("Parent process %d\n",i);//prints out string 100 times each with an incrementing number starting at 0 (0-99)
			usleep(n); //delay for n microseconds
		}
	}
	else{ //if pid is child process
		for(i=0;i<100;i++){
			printf("Child process %d\n",i);//prints out string 100 times each with an incrementing number starting at 0 (0-99)
			usleep(n); //delay for n microseconds
		}
	}
	return 0;
}	
