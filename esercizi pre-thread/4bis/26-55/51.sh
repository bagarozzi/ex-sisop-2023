#!/bin/bash
# puntini.sh

tempo=$1
for (( tempo=$1 ; tempo>0 ; tempo=${tempo}-1 )) ; do
    echo "$$"
    sleep 1
done