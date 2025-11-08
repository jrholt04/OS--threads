#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>
#include "bathroom.h"

int main (int argc, char **argv) {
    pthread_t orc, dwarve, elve;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_create(&orc, &attr, orcs, NULL);
    pthread_create(&elve, &attr, elves, NULL);
    pthread_create(&dwarve, &attr, dwarves, NULL);

    pthread_join(orc, NULL);
    pthread_join(elve, NULL);
    pthread_join(dwarve, NULL);

}

void *elves(void *param){
    while(true){

    }
}

void *dwarves(void *param){
    while(true){

    } 
}

void *orcs(void *param){
    while(true){

    }
}