#!/bin/bash

exec {FD}< ./asteristchi.txt
while read -u ${FD} PRIMA SECONDA TERZA QUARTA QUINTA ; do
    echo "${QUARTA} ${TERZA}"
done