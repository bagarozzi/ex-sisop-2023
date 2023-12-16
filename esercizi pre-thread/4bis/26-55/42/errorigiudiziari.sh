#!/bin/bash

while read IDVERD VERD ; do 
    while read IDENUNCIA IDVERD2 ; do 
        if [[ ${IDVERD2} == ${IDVERD} ]] ; then
            while read NOME COGNOME IDENUNCIA2 MOTIVO ; do  
                if [[ ${IDENUNCIA2} == ${IDENUNCIA} ]] ; then
                    echo "Nome: ${NOME} | Cognome: ${COGNOME} | Motivo: ${MOTIVO} | Verdetto: ${VERD}"
                fi
            done < denunce.txt
            break
        fi
    done < processi.txt
done < verdetti.txt