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

int main (int argc, char **argv) {
    if (argc > 2){
        bathMax = stoi(argv[1]);
    }
    else {
        bathMax = 4;
    }
    
    bathroom = createBathroom(bathroom, bathMax);   //this should be shared 
    pthread_t orc, dwarve, elf;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&species_mutex[0], 0, 0); //elves
    sem_init(&species_mutex[1], 0, 0); //dwarves
    sem_init(&species_mutex[2], 0, 0); //orcs
    
    sem_init(&bath_mutex, 0, 1);

    pthread_create(&orc, &attr, orcs, NULL);
    pthread_create(&elf, &attr, elves, NULL);
    pthread_create(&dwarve, &attr, dwarves, NULL);
   
    pthread_join(orc, NULL);
    pthread_join(elf, NULL);
    pthread_join(dwarve, NULL);

}

Bathroom createBathroom(Bathroom bathroom, int bathMax){
    bathroom.currerntSpecies = "NONE";
    bathroom.countInBath = 0;
    bathroom.bathMax = bathMax;
    return bathroom;
}

void *elves(void *param){
    printf("Elf Ready \n");
    while(true){
        sem_wait(&bath_mutex);
        if ((bathroom.currerntSpecies == "ELF" || bathroom.currerntSpecies == "NONE") && (bathroom.countInBath < bathMax)){
            bathroom.currerntSpecies = "ELF";
            bathroom.countInBath += 1;
            sem_post(&bath_mutex);
 
           printf("[ELF] In bathroom. Count: %d\n", bathroom.countInBath);

            sleep(2); 

            sem_wait(&bath_mutex);
            bathroom.countInBath -= 1;

            printf("[ELF] Leaving bathroom. Remaining: %d\n", bathroom.countInBath);

            if (bathroom.countInBath == 0) {
                bathroom.currerntSpecies = "NONE";
                 if (waitingDwarves > 0) {
                    waitingDwarves--;
                    sem_post(&species_mutex[1]);
                } else if (waitingOrcs > 0) {
                    waitingOrcs--;
                    sem_post(&species_mutex[2]);
                } else if (waitingElves > 0) {
                    waitingElves--;
                    sem_post(&species_mutex[0]);
                }
                
            }
            sem_post(&bath_mutex);
        }   
        else {
            waitingElves += 1;
            sem_post(&bath_mutex);
            sem_wait(&species_mutex[0]);
        }
    }
}

void *dwarves(void *param){
    printf("Dwarf Ready \n");
    while(true){
        sem_wait(&bath_mutex);
        if ((bathroom.currerntSpecies == "DWARF" || bathroom.currerntSpecies == "NONE" ) && (bathroom.countInBath < bathMax)){
            bathroom.currerntSpecies = "DWARF";
            bathroom.countInBath += 1;
            sem_post(&bath_mutex);

            printf("[DWARF] In bathroom. Count: %d\n", bathroom.countInBath);

            sleep(2); 

            sem_wait(&bath_mutex);
            bathroom.countInBath -= 1;

            printf("[DWARF] Leaving bathroom. Remaining: %d\n", bathroom.countInBath);

            if (bathroom.countInBath == 0) {
                bathroom.currerntSpecies = "NONE";
                if (waitingDwarves > 0) {
                    waitingDwarves--;
                    sem_post(&species_mutex[1]);
                } else if (waitingOrcs > 0) {
                    waitingOrcs--;
                    sem_post(&species_mutex[2]);
                } else if (waitingElves > 0) {
                    waitingElves--;
                    sem_post(&species_mutex[0]);
                }
                
            }
            sem_post(&bath_mutex);
        }   
        else {
            waitingDwarves += 1;
            sem_post(&bath_mutex);
            sem_wait(&species_mutex[1]);
        }
        
    } 
}

void *orcs(void *param){
    printf("Orc Ready \n");
    while(true){
       sem_wait(&bath_mutex);
        if ((bathroom.currerntSpecies == "ORC" || bathroom.currerntSpecies == "NONE") && (bathroom.countInBath < bathMax)){
            bathroom.currerntSpecies = "ORC";
            bathroom.countInBath++;
            sem_post(&bath_mutex);

            printf("[ORC] In bathroom. Count: %d\n", bathroom.countInBath);

            sleep(2);

            sem_wait(&bath_mutex);
            bathroom.countInBath--;

            printf("[ORC] Leaving bathroom. Remaining: %d\n", bathroom.countInBath);

            if (bathroom.countInBath == 0) {
                bathroom.currerntSpecies = "NONE";
                printf("species %s \n", bathroom.currerntSpecies.c_str());

                if (waitingDwarves > 0) {
                    waitingDwarves--;
                    sem_post(&species_mutex[1]);
                } else if (waitingOrcs > 0) {
                    waitingOrcs--;
                    sem_post(&species_mutex[2]);
                } else if (waitingElves > 0) {
                    waitingElves--;
                    sem_post(&species_mutex[0]);
                }
                
            }
            sem_post(&bath_mutex);
        }   
        else {
            waitingOrcs += 1;
            sem_post(&bath_mutex);
            sem_wait(&species_mutex[2]);
        }
        
    }
}

