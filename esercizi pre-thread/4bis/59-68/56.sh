#!/bin/bash
# scrivisustderr.sh

while read RIGA ; do 
    echo "${RIGA%% *}" 1>&2
    echo "Evviva" 
done