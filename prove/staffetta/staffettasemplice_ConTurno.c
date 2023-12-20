/* staffettasemplice_ConTurno.c */

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "DBGpthread.h"


#define NUM_ALFA 5
#define NUM_BETA 4

pthread_mutex_t mutex;
pthread_cond_t cond_alfa; /* qui attendono gli alfa */
pthread_cond_t cond_beta; /* qui attendono i beta */

/*per indicare il turno dei corridori alfa*/
int turno_tra_alfa=0;
/*pre indicare il turno dei corridori beta*/
int turno_tra_beta=0;

#define TURNOALFA 0
#define TURNOBETA 1

/* indica quale gruppo di corridori e' di turno, parte per primo un ALFA */
int turno_gruppo = TURNOALFA;  

void *alfa(void *arg){
	char Alabel[128]; 
	char Alabelsignal[128]; 
	int index=*((int*)arg);
	/* NOTA BENE: USERO' IL MIO INDICE come mio turno tra gli alfa */
 	free(arg);

	sprintf( Alabel, "A%d", index);
	sprintf( Alabelsignal, "A%d->B", index);
	pthread_mutex_lock(&mutex);
	while(1){
		/* pthread_mutex_lock(&mutex); */
		/* COMPLETARE */
		/* attendo il mio turno */
		while(turno_gruppo != TURNOALFA || index != turno_tra_alfa){
			pthread_cond_wait(&cond_alfa, &mutex);
		}
		/* parto per il mio giro */
		printf("alfa %d parte\n",index);
		sleep(1);
		printf("alfa %d ha completato il giro\n",index);
		
		/* COMPLETARE */
		/* stabilisco chi e' il successivo corridore alfa */
		turno_tra_alfa++;
		if(turno_tra_alfa == NUM_ALFA){
			turno_tra_alfa = 0;
		}
		/* COMPLETARE */
		/* il prossimo corridore deve essere un beta */
		turno_gruppo = TURNOBETA;
		/* COMPLETARE */
		/* sveglio i beta */
		pthread_cond_broadcast(&cond_beta);
		/* pthread_mutex_unlock(&mutex); */
	}
	pthread_exit(NULL); 
}


void *beta(void *arg){
	char Blabel[128]; 
	char Blabelsignal[128]; 
	int index=*((int*)arg);
	/* NOTA BENE: USERO' IL MIO INDICE come mio turno tra i beta */

 	free(arg);

	sprintf( Blabel, "B%d", index);
	sprintf( Blabelsignal, "B%d->A", index);
	pthread_mutex_lock(&mutex);
	while(1){
		/* pthread_mutex_lock(&mutex);*/ 
		/* COMPLETARE */
		/* attendo il mio turno */
		while(turno_gruppo != TURNOBETA || index != turno_tra_beta){
			pthread_cond_wait(&cond_beta, &mutex);
		}	
		/* parto per il mio giro */
		printf("Beta %d parte\n",index);
		sleep(1);
		printf("Beta %d ha completato il giro\n",index);
		/* COMPLETARE */
		/* stabilisco chi e' il successivo corridore beta */
		turno_tra_beta++;
		if(turno_tra_beta == NUM_BETA){
			turno_tra_beta = 0;
		}
		/* COMPLETARE */
		/* il prossimo corridore deve essere un alfa */
		turno_gruppo = TURNOALFA;
		/* COMPLETARE */
		/* sveglio gli alfa */	
		pthread_cond_broadcast(&cond_alfa);
		/* pthread_mutex_unlock(&mutex); */
	}
	pthread_exit(NULL); 
}

int main(void){
	int rc,i, *p;
	pthread_t th;
	
	rc = pthread_cond_init(&cond_alfa, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&cond_beta, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");
	
	
	/*creo i thread alfa*/
	for(i=0;i<NUM_ALFA;i++) {

                /* alloco la struttura in cui passare i parametri */
                p=malloc(sizeof(int));
                if(p==NULL) {
                        perror("malloc failed: ");
                        exit (1);
                }
                *p=i;

		rc=pthread_create( &th, NULL, alfa, (void*)p ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	/*creo i thread beta*/
	for(i=0;i<NUM_BETA;i++) {

                /* alloco la struttura in cui passare i parametri */
                p=malloc(sizeof(int));
                if(p==NULL) {
                        perror("malloc failed: ");
                        exit (1);
                }
                *p=i;

		rc=pthread_create( &th, NULL, beta, (void*)p ); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 
	return 0;
}
