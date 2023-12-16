# Makefile per infiniti.c
# a causa della presenza di pthread
# occorre compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 
# oppure con  -D_THREAD_SAFE  
# per usare strerror_r devo anche usare _POSIX_C_SOURCE=200112L

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: 	infiniti.exe 

infiniti.exe: infiniti.o
	gcc ${LFLAGS} -o infiniti.exe infiniti.o ${LIBRARIES}

infiniti.o: infiniti.c
	gcc ${CFLAGS} -c infiniti.c 


.PHONY:	clean

clean:
	rm -f infiniti.o infiniti.exe 
