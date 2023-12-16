/* con_trucco.c  */

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

#define NUM_THREADS 5

int N=-1;

void *PrintHello(void *arg)
{
	/* sleep(4); */
	printf("\n %"  PRIiPTR ": Hello World! N=%d\n", (intptr_t)arg, N );
	pthread_exit (NULL);
}

int main()
{
	pthread_t tid;
	int rc;
	intptr_t t = 0;
	while(1){
		printf("Creating thread %" PRIiPTR "\n", t);
		rc = pthread_create (&tid, NULL, PrintHello, (void*)t );
		if (rc){
			char msg[100];
			int ret;
			ret = strerror_r(rc, msg, 100);
			if(ret){
				printf("sterror_r failed: %d", ret);
				exit(1);
			}
			printf("pthread_create failed: %i, %s", rc, msg);
			exit(1);
		}
		t++;
	}

	pthread_exit (NULL);  /* far vedere commentando questa riga */
	return(0);
}
