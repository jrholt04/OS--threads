// sources:
//      stoi: https://www.geeksforgeeks.org/cpp/convert-string-to-int-in-cpp/ Accessed 11/8/25


#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>
#include <string>
#include "bathroom.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc >= 2){
        bathMax = stoi(argv[1]);
    }
    else {
        printf("Usage: ./bathroom <max number in bathroom>\n");
        exit(1);
    }

    pthread_t elfThread[bathMax], dwarfThread[bathMax], orcThread[bathMax];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&bath_mutex, 0, 1);
    sem_init(&dwarf_mutex, 0, 1);
    sem_init(&elf_mutex, 0, 1);
    sem_init(&orc_mutex, 0 , 1);
    sem_init(&printSem, 0, 1);

    //create multiple elves and multiple dwarves
    for (int i = 0; i < bathMax; i++){
        pthread_create(&elfThread[i], &attr, elves, NULL);
    } 
    for (int i = 0; i < bathMax; i++){
        pthread_create(&dwarfThread[i], &attr, dwarves, NULL);
    } 
    for (int i = 0; i < bathMax; i++){
        pthread_create(&orcThread[i], &attr, orcs, NULL);
    } 
    
    for (int i = 0; i < bathMax; i++){
        pthread_join(elfThread[i], NULL);
    }
    for (int i = 0; i < bathMax; i++){
        pthread_join(dwarfThread[i], NULL);
    }
    for (int i = 0; i < bathMax; i++){
        pthread_join(orcThread[i], NULL);
    }
    
}

void *elves(void *param){
    while (true) {
        sem_wait(&elf_mutex);
        waitingElves++;
        sem_wait(&printSem);
        printf("one Elf is waiting to potty\n");
        sem_post(&printSem);
        if (waitingElves == 1){
            sem_wait(&bath_mutex);
        }
        sem_post(&elf_mutex);
        
        countInBath++;  
        
        sem_wait(&printSem);
        printf("Elf is using bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        sleep(2);

        sem_wait(&elf_mutex);
        waitingElves--;
        countInBath--;
        sem_wait(&printSem);
        printf("Elf left bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        if (waitingElves == 0){
            sem_post(&bath_mutex);
        }
        
        sem_post(&elf_mutex);

        sleep(2);
    }
}

void *dwarves(void *param){
    while (true) {
        sem_wait(&dwarf_mutex);
        waitingDwarves++;
        sem_wait(&printSem);
        printf("one dwarf is waiting to potty\n");
        sem_post(&printSem);
        if (waitingDwarves == 1){
            sem_wait(&bath_mutex);    
        }
        sem_post(&dwarf_mutex);
        
        countInBath++;  

        sem_wait(&printSem);
        printf("Dwarf is using bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        sleep(2);

        sem_wait(&dwarf_mutex);
        countInBath--;
        waitingDwarves--;
        sem_wait(&printSem);
        printf("Dwarf left bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        if (waitingDwarves == 0){
            sem_post(&bath_mutex);
        }
        
        sem_post(&dwarf_mutex);

        sleep(2);
    }
}

void *orcs(void *param){
    while (true) {
        sem_wait(&orc_mutex);
        waitingOrcs++;
        sem_wait(&printSem);
        printf("one Orc is waiting to potty\n");
        sem_post(&printSem);
        if (waitingOrcs == 1){
            sem_wait(&bath_mutex);
        }
        sem_post(&orc_mutex);
        
        countInBath++;  
        
        sem_wait(&printSem);
        printf("Orc is using bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        sleep(2);

        sem_wait(&orc_mutex);
        waitingOrcs--;
        countInBath--;
        sem_wait(&printSem);
        printf("Orc left bathroom (remainind %d)\n", (bathMax - countInBath));
        sem_post(&printSem);
        if (waitingOrcs == 0){
            sem_post(&bath_mutex);
        }
        
        sem_post(&orc_mutex);

        sleep(2);
    }
}