#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    srand(123423);
    do{
        if(rand()%3 == 0){
            break;
        }
    }while(1);
    return 0;
}
