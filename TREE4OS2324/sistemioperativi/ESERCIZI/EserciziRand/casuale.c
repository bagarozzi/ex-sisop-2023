/* casuale.c  */

#ifndef _POSIX_SOURCE
	#define _POSIX_SOURCE
#endif

#include <unistd.h>
#include <stdlib.h>		/* serve per la funzione rand */
#include <stdio.h>
#include <time.h>		/* serve per la funzione time */

int main(void) {
	int counter=0;
	srand( time(NULL) );	
	while(1) {
		counter++;
		if( (rand()%10) == 3 ) 
			break;
	}
	printf("estratti %i numeri casuali\n", counter);
	fflush(stdout);

	return(0);
}


