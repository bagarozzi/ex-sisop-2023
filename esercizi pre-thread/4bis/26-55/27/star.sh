#!/bin/bash

exec {FD}< ./asteristchi.txt
while read -u ${FD} PRIMA SECONDA TERZA QUARTA QUINTA ; do
    echo "${QUARTA} ${TERZA}"
done

# in alternativa potevo lanciare lo script dandogli nello stdin il file:
# ./star.sh < asterischi.txt
# e poi eseguire la lettura finché in file non finiva controllandolo con if (( $? == 0 ))