/* Esercizio 3: es3_fachiri
Esistono 2 fachiri e un vettore di 10 spade.
L'accesso a ciascuna spada è protetto da una variabile mutex per ciascuna spada.
I 2 fachiri svolgono continuamente il loro esercizio che consiste nel: 1) prendere uno
dopo l'altra 10 spade. 2) Dopo avere preso tutte le spade, trafiggersi con le spade
stampando poi a video un grido di dolore. 3) Rimettere le spade al loro posto. 4)
ricominciare da capo.
Entrambi i fachiri cominciano a prendere le spade cominciando dalla spada di indice
minore.
Modellare il sistema mediante un thread per ciascun fachiro.
Iniziate l'esercizio scrivendo il Makefile. 
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>	/* uintptr_t */
#include <inttypes.h>	/* PRIiPTR */
#include <pthread.h>
#include <string.h>

const int SWORDS_COUNT = 10;

pthread_mutex_t mutex[10];
pthread_cond_t cond[10];

int SWORDS[10];

void* fachiro(void* arg){
    int i = 0;
    while (1) {
        /* prendo possesso delle spade */
        for(i = 0; i < SWORDS_COUNT; i++) {
            pthread_mutex_lock(&mutex[i]);
            if(SWORDS[i] == 0){
                pthread_cond_wait(&cond[i], &mutex[i]);
            }
        }

        /* sezione critica: trafiggersi e poi rimettere a posto la spada */
        for(i = 0; i < SWORDS_COUNT; i++){
            printf("AHH %d", i);
            SWORDS[i] = 1;
            pthread_cond_signal(&cond[i]);
            sleep(700);
        }
        printf("Ho finito, metto a posto");
        /* fine sezione critica, libero le spade */
        for(i = 0; i < SWORDS_COUNT; i++) pthread_mutex_unlock(&mutex[i]);
    }
}

int main(void){
    int i;
    intptr_t arg = 0;
    pthread_t tid;

    for(i = 0; i < SWORDS_COUNT; i++){
        pthread_mutex_init(&mutex[i], NULL);
        pthread_cond_init(&cond[i], NULL);
        SWORDS[i] = 1; /* tutte le spade sono nel sacco */
    }

    pthread_create(&tid, NULL, fachiro,(void*)arg); /* Creo i due fachiri */
    pthread_create(&tid, NULL, fachiro, (void*)arg);
}