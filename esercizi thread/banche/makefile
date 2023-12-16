CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: banche.exe

banche.exe: banche.o
	gcc -o banche.exe banche.o ${LIBRARIES}

banche.o: banche.c
	gcc ${CFLAGS} -c banche.c

.PHONY: all, clean

clean: 
	rm -f banche.o banche.exe