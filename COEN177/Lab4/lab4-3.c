//Name: Hanna Albright
//Date: January 28, 2021
//Title: Lab4 - Developing multi-threaded applications
//Description: This program fills up two 1024 x 1024  matrices with random integers (using mod 11 to keep the integers small for printing to terminal). I created an array of N integers, N being the number of rows in the final matrix, to keep the iteration number of the thread and row number for the go function. Each thread created takes in their iteration number from the row matrix as a parameter to the go function. The go function calculates the product of the two original matrices for that specified row and stores it in the resulting matrix. Back in the main function, the threads are joined after they are finished with the go function and the resulting matrix is printed to the terminal.
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 1024 //1024 rows and columns for all matrices
#define M 1024
#define L 1024

double matrixA[N][M];//creating matrices
double matrixB[M][L];
double matrixC[N][L];

void *multiply(void *);
pthread_t threads[N];//N number of threads

int main(){
	int j,k,i;
	int row[N]; //array to hold iteration numbers
	srand(time(NULL));
	for (i = 0; i < N; i++){//fill first array with random numbers
		for (j = 0; j < M; j++){
			matrixA[i][j] = rand()%11;
			printf("| %lf  ", matrixA[i][j]);
		}
		printf("| \n");
	}
	printf("MatrixB: \n");
	for (i = 0; i < M; i++){//fill second array with random numbers
		row[i]=i;//store iteration number
		for (j = 0; j < L; j++){
			matrixB[i][j] = rand()%11;
			printf("| %lf  ", matrixB[i][j]);
		}
		printf("| \n");
	}
	for (i=0; i<N; i++){
		pthread_create(&threads[i], NULL, multiply, row+i);//create threads and use a iteration array location as input for the function multiple
	}
	for (i = 0; i < M; i++){
        	pthread_join(threads[i],NULL);//wait for threads and join
        }
	printf("\n");
	for (i = 0; i < N; i++){//print out the resulting matrix
		for (j = 0; j < L; j++){
			printf("| %lf  ", matrixC[i][j]);
		}
		printf("| \n");
	}
	return 0;
}

void *multiply(void *arg){
	int i,j,k;
	i= *(int *)arg;//i is the iteration number
	for (j = 0; j < L; j++){
		double temp;//inialize temporary variable
		temp = 0;
     	for (k = 0; k < M; k++){
        	temp += matrixA[i][k] * matrixB[k][j];//store matrix multiplication in temp
      }
     	matrixC[i][j] = temp;//store temp in the matrix
  }
			return (NULL);
}
