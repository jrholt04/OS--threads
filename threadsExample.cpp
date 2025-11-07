#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
int sum; 
/* this data is shared by the thread(s) */ 
void *runner(void *param); /* threads call this function */ 

int main (int argc, char **argv){
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    /* set the default attributes of the thread */
    pthread_attr_init(&attr);
    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);
    /* wait for the thread to exit */
    for (int i=0;i<atoi(argv[1]);i++) {
        printf("main: %d\n", i);
    }
    pthread_join(tid,NULL);
    printf("sum = %d \n",sum); 
    return 0;
}

/* The thread will execute in this function */
void *runner(void *param) {
    int i, upper = atoi((char*)param);
    sum=0;
    for (i = 1; i <= upper; i++) {
        sum += i;
        printf("runner: %d \n", sum);
    }
    pthread_exit(0);
}
