#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct thargs {
    int remainingChilds;
    char str[100];
    int index;
};

void func(void* p){
    struct thargs* arg = (struct thargs*)p;
    struct thargs* newArg;
    struct thargs* returnStruct;
    int i, rc;
    pthread_t tid;

    sleep(1);

    if(arg->remainingChilds > 1){
        
        for(i = 1; i < arg->remainingChilds; i++){
            newArg = malloc(sizeof(struct thargs));
            if(newArg == NULL){
                printf("Malloc failed");
                exit(-1);
            }
            newArg->remainingChilds = arg->remainingChilds - 1;
            newArg->index = i - 1;
            rc = pthread_create(&tid, NULL, func, (void*)newArg);
            if(rc){
                printf("ERROR; return code from pthread_create() is %d\n",rc);
                exit(-1);
            }
        }

    }

    returnStruct = malloc(sizeof(struct thargs));
    sprintf(returnStruct->str, "%d %d", arg->remainingChilds, arg->index);
    pthread_exit(returnStruct);
}

int main(void){

}
