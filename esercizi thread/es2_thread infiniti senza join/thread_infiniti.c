/* thread_infiniti.c  */

/* messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>	/* uintptr_t */
#include <inttypes.h>	/* PRIiPTR */
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 5

int N=-1;

void *PrintHello(void *arg)
{
	/* sleep(4); */
	printf("\n %"  PRIiPTR ": Hello World!\n", (intptr_t)arg);
	pthread_exit (NULL);
}

int main(void)
{
	pthread_t tid;
	int rc;
	intptr_t t = 0;
    char msg[100];
    do{
		printf("Creating thread %" PRIiPTR "\n", t);
		rc = pthread_create (&tid, NULL, PrintHello, (void*)t );
		if (rc){
			printf("ERROR; return code from pthread_create() is %i \n",rc);
            strerror_r(rc, msg, 100);
            printf("%s", msg);
			exit(1);
		}
        t++;
	}while(1);

	pthread_exit (NULL);  /* far vedere commentando questa riga */
	return(0);
}
