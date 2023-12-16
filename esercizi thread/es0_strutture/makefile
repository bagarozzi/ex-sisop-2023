CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: strutture.exe

strutture.exe: strutture.o
	gcc -o strutture.exe strutture.o ${LIBRARIES}

strutture.o: strutture.c
	gcc ${CFLAGS} -c strutture.c

.PHONY: all, clean

clean: 	
	rm -f strutture.o strutture.exe