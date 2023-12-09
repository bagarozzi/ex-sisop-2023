/* premortem_nano.c  */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
/* per usare nanosleep devo definire il simbolo _POSIX_C_SOURCE
   con un valore maggiore o uguale a 199309L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

typedef struct s{
	unsigned int indice;
	pthread_t tid;
} S;

void *func(void *arg)
{
	struct timespec req={0L,1000000L}, residuo;

	void *pret; int res; pthread_t tid;
	S *p1, *p=(S*)arg;

	printf("indice %d\n", p->indice);fflush(stdout);
	do {
		/*
		printf("indice %d call nanosleep\n", p->indice);fflush(stdout);
		*/
		res=nanosleep( &req, &residuo);
		if( res!=0 && errno!=EINTR ) {
			printf("nanosleep() failed: error %i\n",res);
			fflush(stdout);
			exit(1);
		}
		req=residuo;
	 } while( res!=0 && errno==EINTR);

	p1=malloc(sizeof(S));
	if(p1==NULL) { perror("malloc failed"); exit (1); }
	p1->indice=p->indice+1;
	p1->tid=pthread_self();
	res=pthread_create (&tid, NULL, func, (void*)p1 );
	if (res){ printf("pthread_create() failed: error %i\n", res); exit(1);}

	res=pthread_join( p->tid, &pret );
	if(res!=0){ printf("pthread_join() failed: error %i\n",res); exit(1); }
	free(arg);
	pthread_exit (NULL);
}

int main()
{
	struct timespec req={0L,1000000L};
	int res; pthread_t tid;
	S *p1;

	printf("main indice 0\n"); fflush(stdout);
	nanosleep( &req, NULL);
	p1=malloc(sizeof(S));
	if(p1==NULL) { perror("malloc failed"); exit (1); }
	p1->indice=1;
	p1->tid=pthread_self();
	res=pthread_create (&tid, NULL, func, (void*)p1 );
	if (res){ printf("pthread_create() failed: error %i\n", res); exit(1);}

	printf("fine main\n"); fflush(stdout);
	
	pthread_exit (NULL);
	return(0);
}

