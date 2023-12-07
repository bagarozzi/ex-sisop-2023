#!/bin/bash

for (( CONTO=$#; CONTO>=1; CONTO=$CONTO-1 )) ; do
        RIS="$RIS ${!CONTO}"
done

echo $RIS


