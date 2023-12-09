/* file:  es10_circolareA3_turn.c 
   Routine che fornisce tre passaggi di testimone tra 3 processi
   il primo fa partire il secondo, il secondo fa partire il terzo
   e il terzo fa partire nuovamente il primo e cosi via
   Implementata con una condition variable per ogni pthread.
*/ 

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#else
#if _POSIX_C_SOURCE < 200112L
	#undef  _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#include "printerror.h"
#include "DBGpthread.h"

#define NUMTHREADS 3

/* dati da proteggere */
uint64_t valGlobale=0;

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex; 
pthread_cond_t	 cond; 
int turn=0;

#define MINDELAY 1
#define MAXDELAY 3
void attendi( int secmin, int secmax) {
        int secrandom=0;
        static int inizializzato=0;
        if( inizializzato==0 ) {
                srandom( time(NULL) ); /* serve simbolo  _DEFAULT_SOURCE */
                inizializzato=1;
        }
        if( secmin > secmax ) return;
        else if ( secmin == secmax )
                secrandom = secmin;
        else
                secrandom = secmin + ( random()%(secmax-secmin+1) );
        do {
                /* printf("attendi %i\n", secrandom);fflush(stdout); */
                secrandom=sleep(secrandom);
                if( secrandom>0 )
                        { printf("sleep interrupted - continue\n"); fflush(stdout); }
        } while( secrandom>0 );
        return;
}


void Op1(void) { printf("Op1 fa qualcosa\n");fflush(stdout);
		 attendi(MINDELAY,MAXDELAY);
		 valGlobale=valGlobale+11; 
		 printf("fine Op1 \n");
		 fflush(stdout);
}
void Op2(void) { printf("Op2 fa qualcosa\n");fflush(stdout); 
		 attendi(MINDELAY,MAXDELAY);
		 valGlobale=valGlobale+13; 
		 printf("fine Op2 \n");
		 fflush(stdout);
}
void Op3(void) { printf("Op3 fa qualcosa\n");fflush(stdout);
		 attendi(MINDELAY,MAXDELAY);
		 valGlobale=valGlobale+15; 
		 printf("fine Op3 \n");
		 fflush(stdout);
}

void FuoriMutuaEsclusioneOp1(void) {
	printf("non in mutua esclusione altre Op1 ...\n");
	fflush(stdout);
	attendi(MINDELAY,MAXDELAY);
	printf("fine altre Op1 \n");
	fflush(stdout);
}
void FuoriMutuaEsclusioneOp2(void) {
	printf("non in mutua esclusione altre Op2 ...\n");
	fflush(stdout);
	attendi(MINDELAY,MAXDELAY);
	printf("fine altre Op2 \n");
	fflush(stdout);
}
void FuoriMutuaEsclusioneOp3(void) {
	printf("non in mutua esclusione altre Op3 ...\n");
	fflush(stdout);
	attendi(MINDELAY,MAXDELAY);
	printf("fine altre Op3 \n");
	fflush(stdout);
}


typedef void(*myfunc)(void);
myfunc vetOp[NUMTHREADS];
myfunc vetAltreOp[NUMTHREADS];

void *ThreadFunc (void *arg) 
{ 
	intptr_t indice, nome; char Label[100];

	indice=(intptr_t)arg;
	nome=indice+1;
	sprintf(Label, "T%lu"PRIiPTR , (unsigned long int) nome );
	while(1) {
		/* operazioni NON in sezione critica */
		vetAltreOp[indice]();


		DBGpthread_mutex_lock(&mutex,Label); 

		/* se il precedente ha gia' fatto la signal allora
		   il nostro deve proseguire senza fare la wait
		   */
		while ( turn != indice ) {
			DBGpthread_cond_wait( &cond,&mutex,Label);
			if ( turn != indice ) {
				printf("%" PRIiPTR " SVEGLIATO PER NIENTE !!!!\n", nome); 
				fflush(stdout);

				DBGpthread_cond_signal( &cond, Label); 
			}
		}

		/* SEZIONE CRITICA: chiama Opqualcosa che legge  e cambia la var globale */
		vetOp[indice]();

		printf("%" PRIiPTR " scrive %lu \n", nome, valGlobale ); 
		fflush(stdout);

		turn = (turn+1)%NUMTHREADS;
		/* risveglio un altro, spero il successivo */
		DBGpthread_cond_signal( &cond, Label); 

		/* rilascio mutua esclusione, cosi' il successivo parte */
		DBGpthread_mutex_unlock(&mutex,Label); 
	}
	printf("%" PRIiPTR " termina\n", nome); 
	fflush(stdout);
	pthread_exit(NULL); 
}

 
int main () 
{ 
	pthread_t    th[NUMTHREADS]; 
	int  rc; intptr_t i;
	void *ptr; 

	rc = pthread_mutex_init(&mutex, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	rc = pthread_cond_init(&cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	vetOp[0]=Op1;
	vetOp[1]=Op2;
	vetOp[2]=Op3;
	vetAltreOp[0]=FuoriMutuaEsclusioneOp1;
	vetAltreOp[1]=FuoriMutuaEsclusioneOp2;
	vetAltreOp[2]=FuoriMutuaEsclusioneOp3;

	turn=0;

	for(i=0;i<NUMTHREADS;i++) {
		rc = pthread_create(&(th[i]), NULL, ThreadFunc, (void*)i ); 
		if (rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	for(i=0;i<NUMTHREADS;i++) {
		rc = pthread_join(th[i], &ptr ); 
		if (rc) PrintERROR_andExit(rc,"pthread_join failed");
	}

	rc = pthread_mutex_destroy(&mutex); 
	if(rc) PrintERROR_andExit(rc,"pthread_mutex_destroy failed");
	rc = pthread_cond_destroy(&cond); 
	if(rc) PrintERROR_andExit(rc,"pthread_cond_destroy failed");

	return(0); 
} 
  
  
