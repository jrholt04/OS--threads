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
    bathroom = createBathroom(bathroom, bathMax);

    pthread_t elfThread, dwarfThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&bath_mutex, 0, 1);
    sem_init(&dwarf_mutex, 0, 1);
    sem_init(&elf_mutex, 0, 1);

    //create multiple elves and multiple dwarves 
    pthread_create(&elfThread, &attr, elves, NULL);
    pthread_create(&dwarfThread, &attr, dwarves, NULL);
    

    pthread_join(elfThread, NULL);
    pthread_join(dwarfThread, NULL);
    
}

Bathroom createBathroom(Bathroom bathroom, int bathMax){
    bathroom.currentSpecies = "NONE";
    bathroom.countInBath = 0;
    bathroom.bathMax = bathMax;
    return bathroom;
}

void *elves(void *param){
    while (true) {
        sem_wait(&bath_mutex);
        sem_wait(&dwarf_mutex);

        if (bathroom.countInBath == bathMax){
            waitingElves++;
        }
        else {
            bathroom.countInBath++;
            printf("one elf entered %d ELFs in bathroom\n", bathroom.countInBath);
        }

        if (bathroom.countInBath == 1){
            sem_wait(&elf_mutex); //lock out dwarves
        }
    
        sleep(2);
    
        bathroom.countInBath--; 
        printf("one elf left %d ELFs in bathroom\n", bathroom.countInBath);
        //kick all the elves out if there is waiting dwarves
        if (waitingDwarves > 0){
            bathroom.countInBath = 0;
            printf("all elfs left becasue there are dwarfs waiting count: %d\n", bathroom.countInBath);
        }
        
        printf("one elf left %d ELFs in bathroom\n", bathroom.countInBath);
        if (bathroom.countInBath == 0){
            sem_post(&elf_mutex);
            sem_post(&dwarf_mutex);
        }
        sem_post(&bath_mutex);
    }
}
void *dwarves(void *param){
    while (true) {
        sem_wait(&bath_mutex);
        sem_wait(&elf_mutex);

        if (bathroom.countInBath == bathMax){
            waitingDwarves++;
        }
        else {
            bathroom.countInBath++;
            printf("one dwarf entered %d DWARFs in bathroom\n", bathroom.countInBath);
        }

        if (bathroom.countInBath == 1){
            sem_wait(&dwarf_mutex); //lock out elves
        }

        
        sleep(2);
        
        bathroom.countInBath--; 
        printf("one dwarf left %d DWARFs left \n", bathroom.countInBath);
        //kick all the dwarfs out if there is waiting elfs
        if (waitingElves > 0){
            bathroom.countInBath = 0;
            printf("all dwarfs left becasue there are elfs waiting count: %d\n", bathroom.countInBath);
        }
        
        if (bathroom.countInBath == 0){
            sem_post(&dwarf_mutex);
            sem_post(&elf_mutex);
        }
        sem_post(&bath_mutex);

    }
}
