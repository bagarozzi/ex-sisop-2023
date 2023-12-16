#!/bin/bash
# random.sh

CONTATORE=0
while (( ${RANDOM}%10!=2 )) ; do
    (( CONTATORE=${CONTATORE}+1 ))
done

echo "Contatore: ${CONTATORE}"