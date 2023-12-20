CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: notifica.exe

notifica.exe: notifica.o
	gcc -o notifica.exe notifica.o ${LIBRARIES}

notifica.o: notifica.c
	gcc ${CFLAGS} -c notifica.c

.PHONY: all, clean, sync

clean:
	rm -f notifica.o notifica.exe

sync:
	git add . ; git commit -m "Sync" ; git push