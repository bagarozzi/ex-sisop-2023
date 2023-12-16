#!/bin/bash

echo "Lancio 10 istanze di 51.sh: "

PIDS=`./lanciaeprendipid.sh`
echo "PIDS: ${PIDS}"

for pid in ${PIDS} ; do kill -9 ${pid} ; done