#!/bin/bash
# reversebizzarro.sh

STRINGA="$1"
RES=""
for (( CONTATORE=${#STRINGA} ; CONTATORE>0 ; CONTATORE=${CONTATORE}-1 )) ; do 
    RES="${RES}`echo "${STRINGA}" | cut -b ${CONTATORE},${CONTATORE}`"
done

echo ${RES}

# è un modo molto merdoso ma funziona, parte dall'ultimo carattere e fa la conta ed ogni volta taglia
# l'i-esimo carattere e lo mette nella stringa finale
# il prof lo fa passando con la pipe alla read l'argomento e legge un argomento alla volta, ma così deve
# anche verificare se la stringa sia finita, usando l'exit status del read