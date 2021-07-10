#!/bin/bash
echo "----------FIFO----------"
cat test.txt | ./lab8 2 0
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat test.txt | ./lab8 2 1 
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat test.txt | ./lab8 2 2 
echo "----------End Second Chance----------"
 
echo "FIFO with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./lab8 10 0
cat accesses.txt | ./lab8 50 0
cat accesses.txt | ./lab8 100 0
cat accesses.txt | ./lab8 250 0
cat accesses.txt | ./lab8 500 0
echo
echo "LRU with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./lab8 10 1
cat accesses.txt | ./lab8 50 1
cat accesses.txt | ./lab8 100 1
cat accesses.txt | ./lab8 250 1
cat accesses.txt | ./lab8 500 1
echo
echo "Second Chance with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./lab8 10 2
cat accesses.txt | ./lab8 50 2
cat accesses.txt | ./lab8 100 2
cat accesses.txt | ./lab8 250 2
cat accesses.txt | ./lab8 500 2
echo
