#!/bin/bash
# cerca.sh

# primo argomento è il percorso e secondo argomento è la query

find "$1" -type f -name "$2" -print # sembra che print non serva