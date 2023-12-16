# Makefile per premortem.c
# a causa della presenza di pthread
# occorrerebbe compilare col flag -D_REENTRANT
# oppure con  -D_THREAD_SAFE 
# per ricordarmene, ho inserito i flag anche direttamente nel codice

CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	premortem_nano.exe 

premortem_nano.exe: premortem_nano.o
	gcc -o premortem_nano.exe premortem_nano.o ${LIBRARIES}

premortem_nano.o: premortem_nano.c
	gcc -c ${CFLAGS} premortem_nano.c


.PHONY:	clean

clean:
	rm -f premortem_nano.o premortem_nano.exe 

