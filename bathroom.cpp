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

    pthread_t elf, dwarve;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&bath_mutex, 0, 1);
    sem_init(&species_mutex, 0, 1);

    pthread_create(&elf, &attr, elves, NULL);
    pthread_create(&dwarve, &attr, dwarves, NULL);

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
    printf("Elf Ready\n");
    while (true) {
    
    }
}
void *dwarves(void *param){
    printf("Dwarf Ready\n");
    while (true) {
        
    }
}
