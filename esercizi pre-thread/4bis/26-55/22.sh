#!/bin/bash
# leggere.sh
# devo per forza aprire il file descriptor perché se no la read non si ricorda dove era rimasta al ciclo prima 
# del while

exec {FD}< /usr/include/stdio.h

if (( $? == 0)) ; then
    while read -u {FD} A B C D ; do 
        echo "${C}"
    done
    exec {FD}>&-
fi 