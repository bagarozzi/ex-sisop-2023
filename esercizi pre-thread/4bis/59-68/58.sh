#!/bin/bash
# backslash.sh

STRINGAFINALE=""
while read RIGA ; do
    while (( INDICE<${#RIGA} )) ; do
        CHAR=${RIGA:${INDICE}:1}
        if [[ ${CHAR} == "*" || ${CHAR} == "?" || ${CHAR} == "[" || ${CHAR} == "]" ]] ; then
            STRINGAFINALE="${STRINGAFINALE}\\${CHAR}"
        else 
            STRINGAFINALE="${STRINGAFINALE}${CHAR}"
        fi
        (( INDICE=${INDICE}+1 ))
    done
    echo "${STRINGAFINALE}"
done