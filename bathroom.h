#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string>
#include <semaphore.h>

using namespace std;

void *elves(void *param);
void *dwarves(void *param);

int countInBath = 0;
int waitingElves = 0;
int waitingDwarves = 0;
int bathMax;
sem_t dwarf_mutex;
sem_t elf_mutex;
sem_t bath_mutex;
sem_t printSem;