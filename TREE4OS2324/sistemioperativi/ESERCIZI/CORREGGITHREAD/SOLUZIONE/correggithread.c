/* file:  correggithread.c

	 COSA DEVE FARE IL PROGRAMMA.
   Il main crea 5 thread, pero',
	 dopo avere creato ciascun thread attende che quel thread
	 lo avvisi di proseguire.
	 Ogni thread, dopo essere sato creato, attende 1 secondo
	 e poi avvisa il main di proseguire, 
	 poi attende un secondo e poi termina.
	 Dopo che il main e' stato avvisato di proseguire da un thread,
	 fa la join a quel thread e poi prosegue creando il successivo. 

	 ATTENZIONE: ho inserito qualche errore.

   Implementata con una sola condition variable ed una mutex.
*/ 


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 

#include <stdint.h>    /* definizioni intptr_t */
#include <inttypes.h>  /* definizioni PRIiPTR */

#include <pthread.h> 
#include "printerror.h"
#include "DBGpthread.h"

#define NUMTHREADS 5

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex; 
pthread_cond_t   cond;

void *Thread (void *arg) 
{ 
	uintptr_t mioindice;
	char Label[512];

	mioindice=(intptr_t)arg;
	snprintf( Label, 512, "T%" PRIiPTR "", mioindice );

	sleep(1);

	DBGpthread_mutex_lock(&mutex,Label); 
	printf(" Sono %s e avviso il main\n", Label);
	fflush(stdout);
	DBGpthread_cond_signal(&cond,Label);
	/* rilascio mutua esclusione */
	DBGpthread_mutex_unlock(&mutex,Label); 

	sleep(1);

	pthread_exit(NULL);
} 

int main () 
{ 
	pthread_t    th[NUMTHREADS]; 
	int  rc;
	intptr_t i;
	void *ptr; 

	rc = pthread_cond_init(&cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	DBGpthread_mutex_lock(&mutex,"main"); 

	for( i=0; i<NUMTHREADS; i++ ) {

		rc = pthread_create(&(th[i]), NULL, Thread, (void*)i); 
		if (rc) PrintERROR_andExit(rc,"pthread_create failed");

		DBGpthread_cond_wait(&cond,&mutex,"main");

		rc = pthread_join(th[i], &ptr ); 
		if (rc) PrintERROR_andExit(rc,"pthread_join failed");

	}
	DBGpthread_mutex_unlock(&mutex,"main"); 

	rc = pthread_mutex_destroy(&mutex); 
	if(rc) PrintERROR_andExit(rc,"pthread_mutex_destroy failed");
	rc = pthread_cond_destroy(&cond); 
	if(rc) PrintERROR_andExit(rc,"pthread_cond_destroy failed");

	return(0); 
} 
  
  
