/* messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L, nel caso definirli prima di unistd.h
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>	/* per uintptr_t */
#include <inttypes.h>	/* per PRIiPTR */
#include <pthread.h>

void* func(){
    pthread_exit(NULL);
}

int main(void){
    
    pthread_exit(NULL);
    return 0;
}