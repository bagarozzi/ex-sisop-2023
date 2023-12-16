#!/bin/bash
#sommaquadrati.sh

for number in "$@" ; do
    (( RIS=${RIS}+(${number}*${number}) ))
done

(( RIS=${RIS}-($#*$#+1)/2 )) # ho sottratto la somma di tutti gli elementi fino a $# al posto di fare un for

echo ${RIS}