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
    bathMax = 4;

    pthread_t elfThread, dwarfThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&bath_mutex, 0, 1);
    sem_init(&dwarf_mutex, 0, 1);
    sem_init(&elf_mutex, 0, 1);
    sem_init(&printSem, 0, 1);

    //create multiple elves and multiple dwarves 
    pthread_create(&elfThread, &attr, elves, NULL);
    pthread_create(&dwarfThread, &attr, dwarves, NULL);
    

    pthread_join(elfThread, NULL);
    pthread_join(dwarfThread, NULL);
    
}

void *elves(void *param){
    while (true) {
        waitingElves++;
        sem_wait(&elf_mutex);
        if (!(countInBath == bathMax)){
            sem_wait(&bath_mutex);
            waitingElves--;
            countInBath++; //if room enter bathroom 
        }
        sem_post(&elf_mutex);

        sem_wait(&printSem);
        printf("one elf entered %d elfs in bathroom waiting dwarfs: %d\n", countInBath, waitingDwarves);
        sem_post(&printSem);
        sleep(2);

        sem_wait(&elf_mutex);
        countInBath--;
        
        sem_wait(&printSem);
        printf("one elf entered %d elfs in bathroom waiting dwarfs: %d\n", countInBath, waitingDwarves);
        sem_post(&printSem);

        if (waitingDwarves > 0){
            countInBath = 0;
            sem_post(&bath_mutex);
        }
        else if (countInBath == 0){
            sem_post(&bath_mutex);
        }
        sem_post(&elf_mutex);
    }
}

void *dwarves(void *param){
    while (true) {
        waitingDwarves++;
        sem_wait(&dwarf_mutex);
        if (!(countInBath == bathMax)){
            sem_wait(&bath_mutex);
            waitingDwarves--;
            countInBath++; //if room enter bathroom 
        }
        sem_post(&dwarf_mutex);

        sem_wait(&printSem);
        printf("one dwarf entered %d elfs in bathroom waiting elf: %d\n", countInBath, waitingElves);
        sem_post(&printSem);
        sleep(2);

        sem_wait(&dwarf_mutex);
        countInBath--;
        
        sem_wait(&printSem);
        printf("one elf entered %d dwarfs in bathroom waiting elf: %d\n", countInBath, waitingElves);
        sem_post(&printSem);

        if (waitingElves > 0){
            countInBath = 0;
            sem_post(&bath_mutex);
        }
        else if (countInBath == 0){
            sem_post(&bath_mutex);
        }
        sem_post(&dwarf_mutex);
    }
}
