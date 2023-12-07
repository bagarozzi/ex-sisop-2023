#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int dammi_il_precedente(int num){
    static int precedente = 0;
    int returnValue = precedente;
    precedente = num;
    return returnValue;
}

int main(void){
    do{
        if(dammi_il_precedente(rand())%3 == 0){
            break;
        }
    }while(1);
    return 0;   
}
