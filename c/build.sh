#!/bin/zsh

# Merge Sort:
gcc -g -Wall mergesort.c checkSort.c -o merge

# Sub Array Sum:
gcc -g -Wall subArraySum.c -o subArray

# Code two different hash table implementations and the tester:
gcc -Wall -g hashFall.c hashLink.c hashTest.c -o hashTable
