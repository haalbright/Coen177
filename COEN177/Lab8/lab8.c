// Name: Hanna Albright
// Date: 03/12/21 
// Title: Lab8 – Memory Management 
// Description: This program creates creates a cache to be used by a text files with various page requests. I used switch cases to implemented, FIFO, LRU, and second chance page replacement algorithm. Each page fault is counted and then printed to the terminal so that you can compare the fault numbers between the types of algorithms.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct { 
  int pageno; // -1 for empty
  int refbit; //for second chance
} ref_page;

int findInCache(ref_page* cache, int CACHE_SIZE, int value) {
  int i;
  for (i=0; i<CACHE_SIZE; i++) {
    if (cache[i].pageno == value) return i; //if in cache, return the index number
  }
  return -1; //else return 0;
}

ref_page removePage(ref_page* cache, int CACHE_SIZE, int index) {
  ref_page temp = cache[index]; //store the page number being removed
  int i;
  for (i=index+1; i<CACHE_SIZE; i++) // Shift all pages left
    cache[i-1] = cache[i];
  return temp;//return page removed
}

int main(int argc, char *argv[]){
  int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
  int algorithm = atoi(argv[2]); // 0=FIFO, 1=LRU, 2=2nd chance

  ref_page cache[CACHE_SIZE]; // Cache that stores pages
  char pageCache[100]; // Cache that holds the input from test file
  int pagesStored = 0; // pagesStored == CACHE_SIZE if the cache is full
  int totalFaults = 0; // keeps track of the total page faults
  int i;
  for (i = 0; i < CACHE_SIZE; i++) {//initialize cache array  
    cache[i].pageno = -1;
  }
  while (fgets(pageCache, 100, stdin)){
    int page_num = atoi(pageCache); // Stores number read from file as an int
    int location = findInCache(cache, CACHE_SIZE, page_num);
    if (-1 == location) totalFaults++; // Count faults
    switch (algorithm) {
      case 1: // LRU
        if (-1 != location) cache[pagesStored-1]=removePage(cache, CACHE_SIZE, location); //if found, remove that page and place it at the end of the cache
        // no break
      case 0: // FIFO & LRU
        if (-1 == location) {//if not found
          if (CACHE_SIZE == pagesStored) { //if the array is full
            removePage(cache, CACHE_SIZE, 0);
            pagesStored--;
          }
          cache[pagesStored].pageno = page_num;//add new page to the end
          pagesStored++; //increment cacheSize
        }
        break; // End of FIFO & LRU
      case 2: // 2nd chance
        if (-1 == location) {//if not found
          if (CACHE_SIZE == pagesStored) { //if the array is full
            while (cache[0].refbit == 1) {
              cache[CACHE_SIZE-1]=removePage(cache, CACHE_SIZE, 0);
              cache[CACHE_SIZE-1].refbit = 0;//one chance left
            }
            removePage(cache, CACHE_SIZE, 0);//remove page
            pagesStored--;
          }
          cache[pagesStored].pageno = page_num;//new page with two chances(refbit=0)
          cache[pagesStored].refbit = 0;
          pagesStored++; //Need to keep the value within the cacheSize
        } else {//if found
          cache[location].refbit = 1; //give another chance
        }
        break; // End of 2nd chance
    }
  } // End of while (fgets(pageCache, 100, stdin))
  printf("%d Total Page Faults\n", totalFaults);
  return 0;
}
