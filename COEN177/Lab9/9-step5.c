#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int buffersize, threadnum;

pthread_mutex_t lock;

void *go(char *argv){
  pthread_mutex_lock(&lock);//lock mutex
  char buffer[buffersize];
  FILE *outputfp;
  FILE *inputfp;
  inputfp = fopen(argv, "rb");
  if (inputfp==NULL){
    printf("Error");
    return NULL;
  }
  char outputname[100];
  sprintf(outputname, " destination%d.txt", rand());
  outputfp = fopen(outputname, "wb");
  if (outputfp==NULL){
    printf("Error2");
    return NULL;
  }
  while (fread(buffer,buffersize, 1, inputfp)){
    fwrite(buffer, buffersize, 1, outputfp);
  }
  fclose(inputfp);
  fclose(outputfp);
  pthread_mutex_unlock(&lock);//lock mutex
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_mutex_init(&lock, NULL);//initialize mutex
  threadnum=atoi(argv[3]);
  buffersize=atoi(argv[2]);
  pthread_t threads[threadnum];
  int i;
  for (i = 0; i < threadnum; i++){
    pthread_create(&threads[i], NULL, go, argv[1]);  
   
  }
  for (i = 0; i < threadnum; i++) {//join threads
    pthread_join(threads[i],NULL);
  }
  return 0;
}
