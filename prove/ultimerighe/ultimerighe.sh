#!/bin/bash

secondoargomento=$2
if [[ ${secondoargomento} != "" ]] ; then
    echo "Non è concesso più di un argomento" 1>&2
    exit 1
fi

primoargomento=$1
if [[ -f ${primoargomento} ]] ; then 
    ( sleep 2 ; tail -n 3 ${primoargomento} > OUTPUT.txt ) &
    exit 0
else    
    echo "L'argomento non è un file che esiste" 1>&2
    exit 2
fi

