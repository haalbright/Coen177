// Name: Hanna Albright
// Date: January 21, 2021
// Title: Lab3-Pthreads and inter-process Communication – Pipes
// Description: This program forks into a parent and child. The parent duplicates to send it's stdin to the reader and the child duplicates it's stdout to the writer. Through this process, the stdout from cat/etc/passwd command is piped into the stdin of the grept root command.  

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(int argc,char *argv[]){
	int fds[2];//two file discriptors created
	pipe(fds);//pipe system call
	pid_t pchild = fork();
	if (pchild ==-1){//if fork failed
	printf("Error with fork");
	return 0;
	}
	else if(pchild==0){//if child
		dup2(fds[1],1);//takes from upstream sends it to stdout
		close(fds[0]); //close downstream end
		execlp("cat","cat","/etc/passwd",0);//executecat/etc/passwd file path
		close(fds[1]);//close upstream end
	}
	else {//if parent
		wait(NULL);
		close(fds[1]);//close upstream end
		dup2(fds[0],0);//send what is downstream to stdin
		execlp("grep","grep","root",0);//execute grep root file pile
		close(fds[0]);//close downstream end

	}
	return 0;
}
