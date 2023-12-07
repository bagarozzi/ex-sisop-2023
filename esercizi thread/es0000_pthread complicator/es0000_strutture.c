#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Struttura {
    int n;
    char str[100];
    int index;
};

void func(void* arg){
    struct Struttura* castArg = (struct Struttura*)arg;
    sleep(1000);
    if(castArg->n > 1){
        
    }
}

int main(void){
    return 0;
}
