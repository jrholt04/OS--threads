#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>

void *elves(void *param);
void *dwarves(void *param);
void *orcs(void *param);

int bathroomMax = 10; //default capacity 10
sem_t species_mutex;
sem_t bath_mutex;