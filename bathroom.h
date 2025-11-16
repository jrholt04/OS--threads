// File: bathroom.cpp
// Author: Jackson Holt, Transy U
// Course: CS 3074 Operating Systems
//
// This program simulates a shared bathroom scenario involving three races:
// Elves, Dwarves, and Orcs. Each race can use the bathroom concurrently,
// but only one race can occupy it at a time. The program uses POSIX threads
// and semaphores to synchronize access among threads.
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string>
#include <semaphore.h>

using namespace std;

void *elves(void *param);
void *dwarves(void *param);
void *orcs(void *param);

/// this is representation of the bathroom.
int countInBath;
int waitingElves;
int waitingDwarves;
int waitingOrcs;
int bathMax;
sem_t dwarf_mutex;
sem_t elf_mutex;
sem_t orc_mutex;
sem_t bath_mutex;
sem_t printSem;