//Name: Hanna Albright
//Date: 01/14/21
//Title: Lab2 - Programming in C and use of System Calls
//Description: This is a program that creates a total of seven processes where each process has two children or no children at all. It creates two child processes of the root and then creates an additional two child processes for each of those child processes. Each child prints out its pid and ppid.
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(){
	pid_t pid,pidtwo, pidchild, pidchildtwo;
	pid = fork();
	if (pid == 0){//if child
		printf("Child 1 has a pid=%d and a ppid=%d\n", getpid(), getppid()); //first child of root proces
		pidchild = fork();
		if (pidchild == 0){
			printf("\t Child has a pid=%d and a ppid=%d\n", getpid(), getppid());//child of child 1 (grandchild 1 of root process)
			exit(0);
		}
		if (pidchild == -1){//if fork fails
			printf("Error, system failed %d\n", errno);
		}
		pidchildtwo = fork();
		if (pidchildtwo == 0){
			printf("\t Child has a pid=%d and a ppid%d\n", getpid(), getppid());//child of child 1 (grandchild 2 of root process)
			exit(0);
		}
		if(pidchildtwo == -1){//if fork fails
			printf("Error, system failed %d\n",errno);
		}
		exit(0);
	}
	if (pid == -1){//if fork fails
		printf("Error, system failed %d\n", errno);
    }
	pidtwo = fork();
	if (pidtwo == 0){//if child
		printf("Child 2 has a pid=%d and a ppid=%d\n", getpid(), getppid());//second child of root process
        pidchild = fork();
        if (pidchild == 0){
            printf("\t Child has a pid=%d and a ppid=%d\n", getpid(), getppid());//child of child 2 (grandchild 3 of root process)
            exit(0);
        }
        if (pidchild == -1){ //if fork fails
            printf("Error, system failed %d\n", errno);
        }
        pidchildtwo = fork();
        if (pidchildtwo == 0){
            printf("\t Child has a pid=%d and a ppid=%d\n", getpid(), getppid());//child of child 2 (grandchild 4 of root process)
            exit(0);
        }
        if(pidchildtwo == -1){ //if fork fails
            printf("Error, system failed %d\n",errno);
        }
		exit(0);       
    }
        if (pidtwo == -1){//if fork fails
            printf("Error, system failed %d\n", errno);
        }	
	return 0;
}
