CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: fachiri.exe

fachiri.exe: fachiri.o
	gcc -o fachiri.exe fachiri.o ${LIBRARIES}

fachiri.o: fachiri.c
	gcc ${CFLAGS} -c fachiri.c

.PHONY: clean, all

clean: 
	rm fachiri.o fachiri.exe