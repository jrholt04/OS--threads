#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>

void *elves(void *param);
void *dwarves(void *param);
void *orcs(void *param);

int bathroom[100];
sem_t rw_mutex;
sem_t mutex;