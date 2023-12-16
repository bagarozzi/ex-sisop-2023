#!/bin/bash

exec {FD}< ./RisultatiProvaPratica2.txt

while read -u ${FD} NOME COGNOME MATRICOLA VOTO ; do 
    if [[ VOTO<18 && `grep ${MATRICOLA} ./RisultatiProvaPratica1.txt`==0 ]] ; then
        echo "${MATRICOLA} ${NOME} ${COGNOME} ${VOTO}"
    fi
done

exec {FD}>-