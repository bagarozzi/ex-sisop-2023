/*
    SCHEMA 10 PRODUTTORI 1 CONSUMATORE
*/

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#define THREADSNUM 2

/* variabili di stato e da proteggere */
int tidDisponibile = 0;
pthread_t bufferCondiviso;

/* variabili per la sincronizzazione */
pthread_mutex_t mutex;
pthread_cond_t condBufferDisponibile;
pthread_cond_t condThreadPuoScrivere;

void* notifica(void* arg){
    int rc;
    pthread_t tid;
    pthread_t th = pthread_self();
    printf("Thread %d spawned\n", pthread_self());

    sleep(1);

    pthread_mutex_lock(&mutex);
    while(tidDisponibile != 0){
        pthread_cond_wait(&condThreadPuoScrivere, &mutex);
    }

    tidDisponibile = 1; 
    bufferCondiviso = th;

    printf("Th-%d: rendo disponibile il mio TID\n", pthread_self());
    pthread_cond_signal(&condBufferDisponibile);
    pthread_mutex_unlock(&mutex);

    printf("Th-%d: ora creo un altro thread figlio\n", pthread_self());
    rc = pthread_create(&tid, NULL, notifica, NULL);
    if(rc){
        printf("Problem in pthread_create() of thread %d\n", pthread_self());
        exit(-1);
    }

    pthread_exit(NULL);
}

int main(void){
    pthread_t vth[THREADSNUM];
    pthread_t th;
    int i, rc;

    pthread_cond_init(&condBufferDisponibile, NULL);
    pthread_cond_init(&condThreadPuoScrivere, NULL);
    pthread_mutex_init(&mutex, NULL);


    for(i = 0; i < THREADSNUM; i++){
        rc = pthread_create(&(vth[i]), NULL, notifica, NULL);
        if(rc){
            printf("Problem in main's pthread_create()\n");
            exit(-1);
        }
    }
    while(1){
        pthread_mutex_lock(&mutex);
        while(tidDisponibile == 0){
            pthread_cond_wait(&condBufferDisponibile, &mutex);
        }
        th = bufferCondiviso;
        tidDisponibile = 0;
        
        printf("Main: ricevuto TID da %d, lo aspetto\n", th);       
        pthread_cond_signal(&condThreadPuoScrivere);
        pthread_mutex_unlock(&mutex);

        pthread_join(th, NULL);
        printf("Il main ha atteso correttaente il thread %d\n", th);
    }

    pthread_exit(NULL);
    return 0;
}  
