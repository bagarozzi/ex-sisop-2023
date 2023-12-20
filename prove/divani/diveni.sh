#!/bin/bash

MINWIDTH="$1"
MAXHEIGHT="$2"

exec {FD}< ./divani.txt

while read -u ${FD} NOME LARG ALTZ PROF ; do
    if [[ ( ${LARG}>=${MINWIDTH} ) && ( ${ALTZ}<=${MAXHEIGHT} )]] ; then
        echo "${NOME} ${LARG} ${ALTZ} ${PROF}"
    fi
done