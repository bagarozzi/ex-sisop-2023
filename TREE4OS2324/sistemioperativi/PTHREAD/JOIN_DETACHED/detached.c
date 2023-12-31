/* detached.c  Esempio banale  */

/* gia' messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int Glob=10;
void *do_thread(void *p_index)
{
	int ris;

	Glob+=3;
	printf("thread index %d: Glob=%d thread_ID %u\n", *((int*)p_index), Glob, (int)pthread_self() );

	/* uso in qualche modo l'indice che mi e' stato passato */
	ris =  *((int*)p_index);
	ris = - ris ; /* lo cambio di segno, per gioco */

	/* dealloco la struttura in cui mi sono stati passati i parametri */
	free(p_index);

	pthread_exit ( NULL );  /* valore restituito dal thread */
}

int main()
{
	pthread_t vthreads[NUM_THREADS];
	int rc, t, *p;
	pthread_attr_t attr;

	printf("il main e' il thread con ID %u\n", (int) pthread_self() );

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	for(t=0;t < NUM_THREADS;t++){

		/* alloco la struttura in cui passare i parametri */
		p=malloc(sizeof(int));
		if(p==NULL) {
			perror("malloc failed: ");
			pthread_exit (NULL);
		}
		*p=t;


		/* printf("Creating thread DETACHED %d\n", t); */
		rc = pthread_create (&vthreads[t], &attr, do_thread, p );
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
		else
			printf("Created thread DETACHED ID %u\n", (int)(vthreads[t]) );
		
			
	}
	pthread_attr_destroy(&attr);

	pthread_exit (NULL);
	/* i thread creati continuano l'esecuzione anche dopo la fine del main */
	return(0); /* non viene mai eseguita */

}
