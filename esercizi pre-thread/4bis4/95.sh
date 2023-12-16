#!/bin/bash
# discendenti.sh

if [[ $1 > 0 ]] ; then
    for (( CONTATORE=0 ; CONTATORE<$1; CONTATORE=${CONTATORE}+1 )) ; do 
        ./95.sh $(( $1 - 1 )) &
    done
fi

wait

echo "$1"
exit 0
