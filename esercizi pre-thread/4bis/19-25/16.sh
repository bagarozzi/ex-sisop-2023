#!/bin/bash
# argomenti.sh

STRINGA=""

for (( CONTATORE=0 ; CONTATORE<=$# ; CONTATORE=${CONTATORE}+1 )) ; do 
    (( VAR=${CONTATORE}*2 ))
    STRINGA=${STRINGA}${!VAR}
done

for (( CONTATORE=0 ; CONTATORE<=$# ; CONTATORE=${CONTATORE}+1 )) ; do 
    (( VAR=${CONTATORE}*2 + 1 ))
    STRINGA="${STRINGA}${!VAR}"
done

echo "${STRINGA}"

# I: ciao come stai io sto bene tu tutto ok
# O: comeiobenetuttociaostaistotuok