#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string>
#include <semaphore.h>

using namespace std;

struct Bathroom {
    string currentSpecies;
    int countInBath;
    int bathMax;
};


Bathroom createBathroom(Bathroom bathroom, int bathMax);

void *elves(void *param);
void *dwarves(void *param);

Bathroom bathroom;//at the start there are none of either of the elves waiting
int waitingElves = 0;
int waitingDwarves = 0;
int bathMax;
sem_t dwarf_mutex;
sem_t elf_mutex;
sem_t bath_mutex;