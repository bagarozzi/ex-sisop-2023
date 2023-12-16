#!/bin/bash
# seconda.sh

exec {FD}< "${1}"

while read -u ${FD} PRIMA SECONDA TERZA ; do
    OUT="${OUT}${SECONDA}"
done

echo "${OUT}"