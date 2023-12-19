CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: funivia.exe

funivia.exe: funivia.o
	gcc -o funivia.exe funivia.o ${LIBRARIES}

funivia.o: funivia.c
	gcc ${CFLAGS} -c funivia.c

.PHONY: all, clean

clean:
	rm -f funivia.o funivia.exe