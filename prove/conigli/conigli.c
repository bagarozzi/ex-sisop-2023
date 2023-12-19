#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#define MAXTHREADS 6

pthread_mutex_t mutex;

int actualThreads = 0;

void* func(void* arg){
    int rc, failed = 0;
    pthread_t tid;
    void* uselessArg = NULL;

    rc = pthread_mutex_lock(&mutex);
    if(rc){
        printf("Problem in %d pthread_mutex_lock\n", pthread_self());
        exit(-1);
    }
    printf("Thread %d spawnato! I thread sono %d\n", pthread_self(), actualThreads);
    rc = pthread_mutex_unlock(&mutex);
    if(rc){
        printf("Problem in %d pthread_mutex_unlock\n", pthread_self());
        exit(-1);
    }
    
    while(!failed){
        sleep(5);

        rc = pthread_mutex_lock(&mutex);
        if(rc){
            printf("Problem in %d pthread_mutex_lock\n", pthread_self());
            exit(-1);
        }

        if(actualThreads < 5){
            rc = pthread_create(&tid, NULL, func, uselessArg);
            if(rc){
                printf("Problem in %d pthread_create\n", pthread_self());
                exit(-1);
            }

            actualThreads++;
            rc = pthread_mutex_unlock(&mutex);

            if(rc){
                printf("Problem in %d pthread_mutex_unlock\n", pthread_self());
                exit(-1);
            }
            
            printf("Il thread %d è riuscito a creare un thread!\n", pthread_self());
        }
        else{
            failed = 1;
        }
    }
    actualThreads--;
    printf("Il thread %d non è riuscito a creare un thread, termina :(\n", pthread_self());
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(void){
    void* arg = NULL;
    int rc;
    pthread_t tid;

    actualThreads = 1;
    rc = pthread_mutex_init(&mutex, NULL);
    if(rc){
        printf("Problem in main's pthread_mutex_init\n");
        exit(-1);
    }

    while(1){ /* provo in continuazione a creare un thread */
        sleep(5);
        
        rc = pthread_mutex_lock(&mutex);
        if(rc){
            printf("Problem in main's pthread_mutex_lock\n");
            exit(-1);
        }

        if(actualThreads < 5){
            rc = pthread_create(&tid, NULL, func, arg);
            if(rc){
                printf("Problem in main's pthread_create\n");
                exit(-1);
            }
            actualThreads++;
            printf("Il main crea un thread! Ora sono: %d\n", actualThreads);
        }
        else {
            printf("Il main non è riuscito a creare un thread :(\n");
        }

        rc = pthread_mutex_unlock(&mutex);
        if(rc){
            printf("Problem in main's pthread_mutex_unlock\n");
            exit(-1);
        }
    }

    rc = pthread_mutex_destroy(&mutex);
    if(rc){
        printf("Problem in main's pthread_mutex_destroy\n");
        exit(-1);
    }
    pthread_exit(NULL);
    return 0;
}
