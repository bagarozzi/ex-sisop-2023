#!/bin/bash
# leggerecaratteri.sh
# ugualmente a prima devo aprire un file descriptor perché così il read si ricorda dove era rimasto al ciclo prima
# del file

exec {FD} </usr/include/stdio.h
COUNTER=0

# SEMPRE VERIFICARE CHE IL FILE DESCRIPTOR SI SI APERTO PER BENE, ORA NON L'HO FATTO

while read -u ${FD} -N 1 C; do # questo while durà finché il read raggiunge EOF
    (( COUNTER=${COUNTER}+1))
done
exec {FD}>&-
echo "Contatore: ${COUNTER}"