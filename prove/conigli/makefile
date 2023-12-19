CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: conigli.exe

conigli.exe: conigli.o
	gcc -o conigli.exe conigli.o ${LIBRARIES}

conigli.o: conigli.c
	gcc ${CFLAGS} -c conigli.c

.PHONY: all, clean

clean:
	rm -f conigli.o conigli.exe