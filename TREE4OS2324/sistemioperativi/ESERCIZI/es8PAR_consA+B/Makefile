CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	 es8PAR_consA+B.exe

es8PAR_consA+B.exe:  es8PAR_consA+B.o DBGpthread.o 
	gcc -o es8PAR_consA+B.exe es8PAR_consA+B.o DBGpthread.o ${LIBRARIES}

es8PAR_consA+B.o: es8PAR_consA+B.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} es8PAR_consA+B.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c DBGpthread.c


.PHONY:	clean

clean:
	-rm -f DBGpthread.o  es8PAR_consA+B.o  es8PAR_consA+B.exe


