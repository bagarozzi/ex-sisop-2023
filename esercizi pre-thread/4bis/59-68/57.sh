#!/bin/bash
# separa.sh

PAROLA=$PATH

while [[ -n PAROLA ]] ; do 
    PRIMOPERCORSO="${PAROLA%%:*}"
    echo "${PRIMOPERCORSO} | ${#PRIMOPERCORSO}"
    PRECEDENTE=${PAROLA}
    PAROLA=${PAROLA#*:}
    if [[ ${PAROLA} == ${PRECEDENTE} ]] ; # Se non faccio questo controllo lui quando arriva alla fine andrà a cavare
        break;                             # sempre la stringa che finisce con ":", ma quando arriva all'ultimo percorso
                                            # è come non fare cambiamenti, perché non trova ":" e loopa all'infinito
    fi
done