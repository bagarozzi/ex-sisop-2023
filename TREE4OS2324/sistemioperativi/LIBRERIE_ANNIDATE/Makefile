SHELL=/bin/bash

# NOTA SULLE OPZIONI DI COMPILAZIONE
# 	Ultima modifica 2021-11-06
#
# L'opzione di compilazione -fPIC significa 
# Position-Independent Code e ordina al compilatore
# di generare codice macchina che possa essere caricato
# in un punto qualsiasi dello spazio degli indirizzi.
# Il codice position-independent non potra' contenere
# dei jump ad indirizzi assoluti, ma sfruttera' solo
# jump con indirizzi relativi, inoltre, non potra'
# sfruttare alcuni trucchi osceni per ottimizzazione.
# Scopo del codice position-independent e' quello di
# poter essere collocato, a run-time, a partire da
# un indirizzo qualunque della memoria, indirizzo
# che non e' noto al momento del linking.
# Questo e' utile per il codice che implementa le
# librerie caricate dinamicamente, poiche' queste
# librerie vengono caricate a run-time.
#
# Il flag -shared ordina al linker di creare una libreria condivisa.
#
# I due gruppi di flag che seguono non li ho usati ma li spiego lo stesso.
# I flag -call_shared o -Bdynamic o -dy ordinano al linker di usare SOLO
# la versione condivisa della libreria specificata dal flag -l che segue.
# In questo esempio non li uso perche' e' l'opzione di default.
# I flag -non_shared o -Bstatic o -dn o -static  ordinano al linker di usare
# solo la versione statica della libreria specificata dal flag -l che segue.
# Quindi questi flag possono essere usati piu' volte in una stessa riga di
# comando di linking per specificare versioni statiche o condivise di ciascuna libreria.

#
# Occorre capire cosa e' il SONAME
#
# Ogni shared library ha:

# - un SONAME, ossia una stringa che soddisfa il pattern 
#	"lib[NAME][API-VERSION].so.[major-version]" 
#	(dove API-VERSION è solitamente vuoto);
#	Quando cambio molto le API della libreria incremento lo API-VERSION.
#	Nel nostro esempio i SONAME sono libfunzioni1shared.so e 
#	libfunzioni2shared.so perche' non voglio usare versioni. 
# - un REALNAME ossia una stringa che soddisfa il pattern 
#	"SONAME.[MINOR-NUMBER].[RELEASE-NUMBER]" ed è solitamente il nome 
#	del file che concretamente è presente nel file system.
#	Estendendo SONAME, il pattern di REALNAME è 
#	"lib[NAME][API-VERSION].so.[MAJOR-VERSION].[MINOR-VERSION].[RELEASE-NUMBER]";
#	Nel nostro esempio i REALNAME sono libfunzioni1shared.so e 
#	libfunzioni2shared.so perche' non voglio usare versioni e nemmeno
#	MAJOR e MINOR VERSION. 
# - un LINKER NAME, ossia una stringa che da usare sul linker che identifica
#	la libreria stessa.
#	Nel nostro esempio i LINKERNAME sono funzioni1shared e 
#	funzioni2shared.
# NOTARE CHE IL REALNAME E' UNA ESTENSIONE DEL SONAME.


# LA VARIABILE INSTALLDIR_BASE E' LA DIRECTORY CHE A RUNTIME CONTIENE LE
# DUE DIRECTORY lib_1 e lib_2 CON LE LIBRERIE CONDIVISE CREATE.

DIR_BASE=.

INSTALLDIR_BASE=${DIR_BASE}/lib

# directory in cui installare libreria libfunction1: e' locazione a runtime
INSTALLDIR_1=${INSTALLDIR_BASE}/lib_1
# directory in cui installare libreria libfunction2: e' locazione a runtime
INSTALLDIR_2=${INSTALLDIR_BASE}/lib_2


# opzioni di compilazione comuni a tutti i sorgenti C
CFLAGS=-ansi -Wpedantic -Wall
LFLAGS=

# l'eseguibile sta nella directory di sviluppo, le librerie nelle dir di installazione
TARGETS=${INSTALLDIR_2}/libfunzioni2shared.so ${INSTALLDIR_1}/libfunzioni1shared.so progr1_sharedlib.exe

# All -rpath arguments are concatenated and passed to the runtime linker,
# which uses them to locate shared objects at runtime.

# il primo target specifica le dipendenze principali
# comunemente il primo target viene indicato con la parola all
all:	${TARGETS}


${INSTALLDIR_2}/libfunzioni2shared.so:	createDir2 libfunzioni2shared.so
	cp libfunzioni2shared.so ${INSTALLDIR_2}/

# ATTENZIONE, i flag -Wl vanno messi dopo i -o e dopo i moduli
libfunzioni2shared.so:	funzioni2shared.o
	gcc -shared ${LFLAGS} -fPIC \
	-o libfunzioni2shared.so funzioni2shared.o \
	-Wl,-soname,libfunzioni2shared.so 


funzioni2shared.o:	funzioni2.c
	gcc -c -fPIC ${CFLAGS} -o funzioni2shared.o  funzioni2.c 


${INSTALLDIR_1}/libfunzioni1shared.so:	createDir1 libfunzioni1shared.so
	cp libfunzioni1shared.so ${INSTALLDIR_1}/


# ATTENZIONE, i flag -Wl -l e -L vanno messi dopo -o e dopo i moduli
#
# VERIFICARE col comando:   readelf -d libfunzioni1shared.so
# che libreria 1 "(NEEDED) Shared library: [libfunzioni2shared.so] 
# Oppure alternativamente verificare col comando:  ldd libfunzioni1shared.so
#
# NOTARE CHE LA CREAZIONE DELLA LIBRERIA libfunzioni1 DIPENDE DALLA LIBRERIA
# libfunzioni2 NELLA LOCAZIONE A LINK TIME, NON NELLA LOCAZIONE A RUN TIME
#
# Il flag -shared ordina al linker di creare una libreria condivisa.

libfunzioni1shared.so:	${INSTALLDIR_2}/libfunzioni2shared.so funzioni1shared.o
	gcc -shared ${LFLAGS} -fPIC    \
		-o libfunzioni1shared.so funzioni1shared.o \
		-Wl,-soname,libfunzioni1shared.so \
		-lfunzioni2shared -L. \
		-Wl,-rpath,${INSTALLDIR_2} 



funzioni1shared.o:	funzioni1.c funzioni2.h
	gcc -c -fPIC ${CFLAGS} -o funzioni1shared.o  funzioni1.c  


progr1.o:	progr1.c funzioni1.h
	gcc -c ${CFLAGS} progr1.c

# NOTARE CHE LA CREAZIONE DELL'ESEGUIBILE DIPENDE DALLA LIBRERIA
# NELLA LOCAZIONE A LINK TIME, NON NELLA LOCAZIONE A RUN TIME
progr1_sharedlib.exe:	progr1.o libfunzioni1shared.so
	gcc ${LFLAGS} \
		-o progr1_sharedlib.exe progr1.o      \
		-lfunzioni1shared \
		-L. \
		-Wl,-rpath,${INSTALLDIR_1}


.PHONY:         clean distclean createDir1 createDir2 createDirs

clean:	
		-rm -f *.exe *.o *.a *.so *~ 

distclean:
		-rm -f ${INSTALLDIR_1}/libfunzioni1shared.so \
			${INSTALLDIR_2}/libfunzioni2shared.so
		-rmdir	${INSTALLDIR_1}
		-rmdir	${INSTALLDIR_2}
		-rmdir	${INSTALLDIR_BASE}

createDirs:	createDir1 createDir2


createDir1:
	if [ ! -e ${INSTALLDIR_BASE} ]; then mkdir -p ${INSTALLDIR_BASE}; fi
	if [ ! -e ${INSTALLDIR_1} ]; then mkdir -p ${INSTALLDIR_1}; fi

createDir2:
	if [ ! -e ${INSTALLDIR_BASE} ]; then mkdir -p ${INSTALLDIR_BASE}; fi
	if [ ! -e ${INSTALLDIR_2} ]; then mkdir -p ${INSTALLDIR_2}; fi

