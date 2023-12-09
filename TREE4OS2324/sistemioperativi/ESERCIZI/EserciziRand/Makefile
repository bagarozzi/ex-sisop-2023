CFLAGS=-ansi -Wpedantic -Wall -Werror -D_POSIX_SOURCE
LFLAGS=
LIBRARIES=

all: 	casuale.exe 

casuale.exe: casuale.o
	gcc ${LFLAGS} -o casuale.exe casuale.o ${LIBRARIES}

casuale.o: casuale.c
	gcc ${CFLAGS} -c casuale.c


.PHONY:	clean

clean:
	rm -f casuale.o casuale.exe 

