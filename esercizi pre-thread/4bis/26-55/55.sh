#!/bin/bash
# lanciaricorsivo.sh

ARG=$1
if (( ARG>0 )) ; then
    ./55.sh $(( $ARG-1 )) &
    echo "Lanciato $!"
    wait $!
else 
    echo "Ultimo script lanciato"
fi