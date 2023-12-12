#!/bin/bash
# elenco.sh

TOTALFILES=0
NAMELENGTH=0

for name in `ls` ; do 
    if [[ -d ${name} ]] ; then 
        (( TOTALFILES=${TOTALFILES}+1 ))
        (( NAMELENGTH=${NAMELENGTH}+${#name} ))
    fi
done

echo "Total files: ${TOTALFILES}"
echo "Total name lenght: ${NAMELENGTH}"