/* joinable.c  Esempio banale  */

/* gia' messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 20

struct thargs {
    pthread_t father_tid;
    int index;
};

void *do_thread(void *p_index)
{
    struct thargs* arg = (struct thargs*)p_index;
    struct thargs* newArg;
    int rc;
    pthread_t tid;
    
    printf("TH-%d: Il mio indice è: %d\n", pthread_self(), arg->index); /* Stampo l'indice */
     
	usleep(1000); /* Wait 1000 microsec */

    if(arg->index < MAX_THREADS) {
        newArg = malloc(sizeof(struct thargs));
        if(newArg == NULL){
            perror("Malloc failed: ");
            pthread_exit(NULL);
        }
        newArg->index = arg->index + 1;
        newArg->father_tid = pthread_self();
        printf("TH-%d: Creo un figlio con indice %d\n", pthread_self(), ++arg->index);
        rc = pthread_create(&tid, NULL, do_thread, (void*)newArg);
        if(rc){
            printf("ERROR; return code from pthread_create() is %d\n",rc);
            exit(-1);
        }
        rc = pthread_join(arg->father_tid, NULL);
        if(rc){
            printf("Join failed!");
            exit(-1);
        }
    }
    else {
        printf("TH-%d: Sono l'ultimo, termino\n");
    }
    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
	int rc;
    struct thargs* p;
    pthread_t tid;

	printf("Il main e' il thread con indice 0\n"); /* Main spawnato   */

    usleep(1000); /* Aspetta 1000 microsec */

    p = malloc(sizeof(struct thargs));
    if(p == NULL) {
        perror("malloc failed: ");
        pthread_exit (NULL);
    }
    p->index = 1;
    p->father_tid = pthread_self();

    rc = pthread_create (&tid, NULL, do_thread, (void*)p); /* Crea un figlio con indice 1 e poi quitta */
    if (rc){ 
        printf("ERROR; return code from pthread_create() is %d\n",rc);
        exit(-1);
    }
	pthread_exit (NULL); /* Il main termina */
	return(1);
}
