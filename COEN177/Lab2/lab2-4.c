//Name: Hanna Albright
//Date: 01/14/21
//Title: Lab2 - Programming in C and use of Systems Calls
//Description: This program creates a fork and the child process prints out contents of the directory. The parent process waits for the child process to finish and and prints out "Child Complete".
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
	pid_t pid;
	printf("\n Before forking. \n");
	pid = fork(); //fork and returns 0 for child or parent process id
	if (pid == -1){ //if system fails
		fprintf(stderr, "can't fork, error %d\n", errno); //prints standard error message and error number
	}
	if(pid == 0){ //if child
		execlp("/bin/ls", "ls", NULL);//print out content of directory
	}
	else{//if parent
		wait(NULL);//wait for child
	        printf("Child Complete");
	        exit(0);//exit
	}
	return 0;
}	
