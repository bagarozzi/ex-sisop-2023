#!/bin/bash

for (( CONT=2 ; CONT<=$# ; CONT=${CONT}+2 )) ; do # indice pari
    echo `wc -l ${!CONT}`
done

for (( CONT=1 ; CONT<=$# ; CONT=${CONT}+2 )) ; do # indice dispari
    echo `wc -l ${!CONT}` 1>&2
done
