/* messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>	/* per uintptr_t */
#include <inttypes.h>	/* per PRIiPTR */
#include <pthread.h>

#define NUM_THREADS 1000

int N=-1;

void *PrintHello(void *arg)
{
	sleep(4);
	printf("\n %"  PRIiPTR ": Hello World! N=%d\n", (intptr_t)arg, N );
	pthread_exit (NULL);
}

int main()
{
	pthread_t vth[NUM_THREADS];
	int rc, i;
	intptr_t t = 0;
	while(1){
		for(i = 0; i < NUM_THREADS; i++){
			printf("Creating thread %" PRIiPTR "\n", t);
			rc = pthread_create (&vth[i], NULL, PrintHello, (void*)t );
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
		printf("Waiting for all threads to end...\n");
		for(i = 0; i < NUM_THREADS; i++){
			rc = pthread_join(vth[i], NULL);
			if (rc){
				char msg[100];
				int ret;
				ret = strerror_r(rc, msg, 100);
				if(ret){
					printf("sterror_r failed: %d", ret);
					exit(1);
				}
				printf("pthread_join failed: %i, %s", rc, msg);
				exit(1);
			}
		}
		printf("Threads ended, creating some more\n");
	}

	pthread_exit (NULL);  /* far vedere commentando questa riga */
	return(0);
}
