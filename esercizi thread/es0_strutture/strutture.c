#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

struct thargs {
    int remainingChilds;
    char str[100];
    int index;
};

void* func(void* p){
    struct thargs* arg = (struct thargs*)p;
    struct thargs* newArg;
    struct thargs* returnStruct;
    int i, rc;
    pthread_t vth[arg->remainingChilds];

    sleep(1000); /* Aspetta un secondo */

    if(arg->remainingChilds > 1){ /* Controlla se deve fare altri figli */
        
        for(i = 0; i < arg->remainingChilds; i++){ /* Li crea tutti passando n-1 ed un index unico */
            newArg = malloc(sizeof(struct thargs));
            if(newArg == NULL){
                printf("Malloc failed");
                exit(-1);
            }
            newArg->remainingChilds = arg->remainingChilds - 1;
            newArg->index = i;
            rc = pthread_create(&vth[i - 1], NULL, func, (void*)newArg);
            if(rc){
                printf("ERROR; return code from pthread_create() is %d\n",rc);
                exit(-1);
            }
        }

        for(i = 0; i < arg->remainingChilds; i++){
            rc = pthread_join(vth[i], (void**)&returnStruct);
            if(rc){
                printf("There was a problem with pthread_join: %d", rc);
                exit(-1);
            }
            printf("Received: \"%s\"\n", returnStruct->str);
            free(returnStruct);
        }

    }

    returnStruct = malloc(sizeof(struct thargs));
    sprintf(returnStruct->str, "%d %d", arg->remainingChilds, arg->index);
    pthread_exit(returnStruct);
}

int main(void){
    struct thargs* arg;
    int rc, i;
    pthread_t vth[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; i++){
        arg = malloc(sizeof(struct thargs));
        arg->index = i;
        arg->remainingChilds = NUM_THREADS - 1;

        rc = pthread_create(&vth[i], NULL, func, (void*)arg);
        if(rc){
            printf("pthread_create failed: %d", rc);
            exit(-1);
        }
    }

    for(i = 0; i < NUM_THREADS; i++){
        rc = pthread_join(vth[i], (void*)&arg);
        if(rc){
            printf("pthread_join failed: %d", rc);
            exit(-1);
        }
        printf("Main received: \"%s\"", arg->str);
    }

    pthread_exit(NULL);
    return 0;
}
