#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>

int shared = rand() % 40;
int read_count = 0;
sem_t rw_mutex;
sem_t mutex;

void *writer(void *arg);
void *reader(void *arg);

int main (int argc, char **argv) {
    pthread_t read, write;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    printf("the start is %d \n", shared);

    pthread_create(&read, &attr, reader, NULL);
    pthread_create(&write, &attr, writer, NULL);

    pthread_join(write, NULL);
    pthread_join(read, NULL);
   
}

void *reader(void *arg){
    while(true){
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1){
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        
        printf("Reading: %d\n", shared);
        sleep(1);
        
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0){
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg){
    while(true){
        sem_wait(&rw_mutex);
        
        shared = rand() % 40;
        printf("Writing: %d\n", shared);
        sleep(1);

        sem_post(&rw_mutex);
    }
}