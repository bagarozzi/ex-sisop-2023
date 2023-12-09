CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE

LIBRARIES=-lpthread

all: 	correggithread.exe

correggithread.exe: correggithread.o DBGpthread.o
	gcc -o correggithread.exe correggithread.o DBGpthread.o ${LIBRARIES}

correggithread.o: correggithread.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} correggithread.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY:	clean

clean:
	-rm -f correggithread.o DBGpthread.o correggithread.exe


