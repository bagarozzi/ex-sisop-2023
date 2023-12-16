# Makefile per con_trucco.c
# a causa della presenza di pthread
# occorre compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 
# oppure con  -D_THREAD_SAFE  
# per usare strerror_r devo anche usare _POSIX_C_SOURCE=200112L

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: 	thread_infiniti.exe 

thread_infiniti.exe: thread_infiniti.o
	gcc ${LFLAGS} -o thread_infiniti.exe thread_infiniti.o ${LIBRARIES}

thread_infiniti.o: thread_infiniti.c
	gcc ${CFLAGS} -c thread_infiniti.c 


.PHONY:	clean

clean:
	rm -f thread_infiniti.o thread_infiniti.exe 