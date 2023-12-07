CFLAGS=-ansi -Wall -Wpedantic -Werror

all: casuale.exe

casuale.exe: casuale.o
	gcc -o casuale.exe casuale.o

causale.o: casuale.c
	gcc ${CFLAGS} -c casuale.c

.PHONY: clean

clean:
	rm -f casuale.o casuale.exe