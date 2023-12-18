#!/bin/bash

exec {FD}< ./cadutevic.txt

echo "" > finale.txt # creo un file intermedio

while read -u ${FD} ANNO LOCAL MOTIVO DANNI ; do 
    OCCORRENZE=`grep -h -c "${MOTIVO}" finale.txt`
    if [[ ${OCCORRENZE} == 0 ]] ; then
        echo "${MOTIVO} `grep -h -c ${MOTIVO} cadutevic.txt`" >> finale.txt 
    fi
done

cat finale.txt