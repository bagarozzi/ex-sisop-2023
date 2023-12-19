#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#define SOBERUSER 4
#define DRUNKUSER 2
#define POSTIFUNIVIA 2
#define TOTALUSERS 6

#define SOBERUSER_CODE 1
#define DRUNKUSER_CODE 0

#define UBRIACO_A_BORDO 1
#define SOBRIO_A_BORDO 2
#define VUOTA 0
#define PIENA 3

intptr_t cabina[POSTIFUNIVIA];
int statoFunivia = VUOTA;
int esclamazioni = 0;

pthread_mutex_t mutex; /* mutex che protegge il vettore funivia e la variabile di stato */
pthread_cond_t funiviaLibera; /* per segnalare che possono iniziare a salire */
pthread_cond_t funiviaRiempita; /* una volta che la cabina è piena la funivia parte */
pthread_cond_t funiviaMeta; /* per segnalare che la funivia è a metà e fare yuppi */

void* utente(void* arg){
    intptr_t indice = (intptr_t)arg;
    int userType;

    if(indice <= 3) userType = SOBERUSER_CODE;
    else userType = DRUNKUSER_CODE;

    printf("Spawnato thread di tipo %d con indice %ld\n", userType, indice);

    while(1){
        pthread_mutex_lock(&mutex);
        while(statoFunivia != VUOTA){
            pthread_cond_wait(&funiviaLibera, &mutex);
        }

        if(statoFunivia == VUOTA){
            cabina[0] = indice;
            printf("L'utente %ld ha preso posto per primo\n", indice);
            if(userType == DRUNKUSER_CODE){
                statoFunivia = UBRIACO_A_BORDO;
                pthread_cond_signal(&funiviaRiempita);
            }
            else if(userType == SOBERUSER_CODE){
                statoFunivia = SOBRIO_A_BORDO;
            }

            pthread_cond_wait(&funiviaMeta, &mutex);
            printf("Utente-%ld: sono a metà yuppi!\n", indice);
            esclamazioni++;
            pthread_cond_signal(&funiviaMeta);
        }
        else if(statoFunivia == SOBRIO_A_BORDO && userType == SOBERUSER_CODE){
            cabina[1] = indice;
            printf("L'utente %ld ha preso posto per secondo\n", indice);
            statoFunivia = PIENA;
            pthread_cond_signal(&funiviaRiempita);

            pthread_cond_wait(&funiviaMeta, &mutex);
            printf("Utente-%ld: sono a metà yuppi!\n", indice);
            esclamazioni++;
            pthread_cond_signal(&funiviaMeta);
        }
        else if(statoFunivia == PIENA || statoFunivia == UBRIACO_A_BORDO){
            printf("Utente-%ld: La funivia è già piena, torno ad aspettare :(\n", indice);
            pthread_mutex_unlock(&mutex);
        }
    }
}

void* funivia(void* arg){
    int i; 
    pthread_mutex_lock(&mutex);
    while(1){
        /* Svuotamento della funivia */
        statoFunivia = VUOTA;
        for(i = 0; i < POSTIFUNIVIA; i++){
            cabina[i] = 0;
        }
        printf("La funivia è pronta per partire!\n");
        /* La funivia manda il segnale ai thread di popolare la cabina e poi aspetta che sia piena */
        pthread_cond_broadcast(&funiviaLibera);
        pthread_cond_wait(&funiviaRiempita, &mutex);

        printf("Gli utenti sono saliti, si parte!\n");
        sleep(1);
        pthread_cond_broadcast(&funiviaMeta);
        while(esclamazioni != 0){
            pthread_cond_wait(&funiviaMeta, &mutex);
        }
        sleep(1);

        printf("Funivia arrivata, tutti giù!\n");
        statoFunivia = VUOTA;
        for(i = 0; i < POSTIFUNIVIA; i++){
            cabina[i] = 0;
        }
        esclamazioni = 0;
        sleep(5);
    }
}

int main(void){
    intptr_t userIndex = 0;
    int i, rc;
    pthread_t tid;

    pthread_cond_init(&funiviaLibera, NULL);
    pthread_cond_init(&funiviaRiempita, NULL);
    pthread_cond_init(&funiviaMeta, NULL);
    pthread_mutex_init(&mutex, NULL);
    statoFunivia = VUOTA;
    for(i = 0; i < POSTIFUNIVIA; i++){
        cabina[i] = 0;
    }

    rc = pthread_create(&tid, NULL, funivia, (void*)userIndex);
    if(rc){
        printf("There was a problem in creating funivia thread");
    }
    
    for(i = 0; i < TOTALUSERS; i++){
        userIndex = i;
        rc = pthread_create(&tid, NULL, utente, (void*)userIndex);
        if(rc){
            printf("There was a problem in creating %d thread", i);
        }
    }

    pthread_cond_destroy(&funiviaLibera);
    pthread_cond_destroy(&funiviaRiempita);
    pthread_cond_destroy(&funiviaMeta);
    pthread_mutex_destroy(&mutex);
    return 0;   
}
