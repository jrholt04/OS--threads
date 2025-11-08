// sources:
//      stoi: https://www.geeksforgeeks.org/cpp/convert-string-to-int-in-cpp/ Accessed 11/8/25


#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>
#include <string>
#include "bathroom.h"

int main (int argc, char **argv) {

    bathroomMax = stoi(argv[0]);
    int numOfElves = rand() % 2*bathroomMax;
    int numOfDwarves = rand() % 2*bathroomMax;
    int numOfOrcs = rand() % 2*bathroomMax; 

    pthread_t orc, dwarve, elf;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_create(&orc, &attr, orcs, NULL);
    pthread_create(&elf, &attr, elves, NULL);
    
    for (int i = 0; i < numOfDwarves; i++){
        pthread_create(&dwarve, &attr, dwarves, NULL);
    }

    pthread_join(orc, NULL);
    pthread_join(elf, NULL);

    for (int i = 0; i < numOfDwarves; i++){
        pthread_join(dwarve, NULL);
    }

}

void *elves(void *param){
    while(true){
        sem_wait(&bath_mutex);
        
        sem_post(&bath_mutex);
    }
}

void *dwarves(void *param){
    while(true){
        sem_wait(&species_mutex);

        sem_post(&species_mutex);
    } 
}

void *orcs(void *param){
    while(true){
        sem_wait(&bath_mutex);

        sem_post(&bath_mutex);
    }
}