#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string>
#include <semaphore.h>

using namespace std;

struct Bathroom {
    string currerntSpecies;
    int countInBath;
    int bathMax;
};


Bathroom createBathroom(Bathroom bathroom, int bathMax);

void *elves(void *param);
void *dwarves(void *param);
void *orcs(void *param);

Bathroom bathroom;//at the start there are none of either of the elves waiting
int waitingElves = 0;
int waitingDwarves = 0;
int waitingOrcs = 0; 
int bathMax = 4; //default capacity 10
sem_t species_mutex[3];
sem_t bath_mutex;