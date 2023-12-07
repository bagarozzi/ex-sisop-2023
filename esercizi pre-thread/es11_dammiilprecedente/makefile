CFLAGS=-ansi -Wall -Wpedantic -Werror

all: dammiprecedente.exe

dammiprecedente.exe: dammiprecedente.o
	gcc -o dammiprecedente.exe dammiprecedente.o

causale.o: dammiprecedente.c
	gcc ${CFLAGS} -c dammiprecedente.c

.PHONY: clean

clean:
	rm -f dammiprecedente.o dammiprecedente.exe