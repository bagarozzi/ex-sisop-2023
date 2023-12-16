#!/bin/bash

# Creo 10 directory
for (( CONTATORE=0 ; CONTATORE<10 ; CONTATORE=${CONTATORE}+1 )) ; do
    mkdir -p deleteme/"1.${CONTATORE}"
done

sleep 4

# Rinomino 10 directory
for (( CONTATORE=0 ; CONTATORE<10 ; CONTATORE=${CONTATORE}+1 )) ; do
    mv deleteme/"1.${CONTATORE}" deleteme/"2.${CONTATORE}"
done

sleep 4

# rimuovo dopo che ho fatto
for (( CONTATORE=0 ; CONTATORE<10 ; CONTATORE=${CONTATORE}+1 )) ; do
    rm -r deleteme
done