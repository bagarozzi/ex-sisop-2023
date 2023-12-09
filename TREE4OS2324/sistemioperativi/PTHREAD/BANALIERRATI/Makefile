# MakefileBanali

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: banale_moltoerrato.exe banale_errato.exe

banale_moltoerrato.exe: banale_moltoerrato.o
	gcc ${LFLAGS} -o banale_moltoerrato.exe banale_moltoerrato.o ${LIBRARIES}

banale_moltoerrato.o: banale_moltoerrato.c
	gcc -c ${CFLAGS} banale_moltoerrato.c

banale_errato.exe: banale_errato.o
	gcc -o banale_errato.exe banale_errato.o ${LIBRARIES}

banale_errato.o: banale_errato.c
	gcc -c ${CFLAGS} banale_errato.c

.PHONY:	clean

clean:
	rm -f banale_moltoerrato.exe banale_errato.exe banale_moltoerrato.o banale_errato.o

