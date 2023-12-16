#!/bin/bash
# unasiunano.sh

SI=1
while read RIGA ; do
    if(( ${SI} == 1 )) ; then
        echo "${RIGA}"
        SI=0
    else
        SI=1
    fi
done