#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int buffersize=atoi(argv[2]);
  char buffer[buffersize]; 
  FILE *outputfp;
  FILE *inputfp;
  inputfp = fopen(argv[1], "rb");
  outputfp = fopen("deleteMe.txt", "wb");
  while (fread(buffer,buffersize, 1, inputfp)){
    fwrite(buffer, buffersize, 1, outputfp);
  }
  fclose(inputfp);
  fclose(outputfp);
}
