#include <stdio.h>
#include <stdlib.h>
#include "macrodi_es2_allocavettore.h"


int main(void){
    int *p, i;
    ALLOCAVETTORE(p)
    if(p != NULL) {
        for(i = 0; i < 10; i++){
            p[i] = -19 + i; 
        }
        printf("Vettore allocato e valore cambiato!\n");
    }
    else {
        printf("Vettore non allocato correttamente.\n");
    }
    return 0;
}
