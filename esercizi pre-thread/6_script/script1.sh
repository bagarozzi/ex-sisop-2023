#!/bin/bash

RIS=""

for (( CONTO=1; CONTO<=$#; CONTO=$CONTO+1 )) ; do	
	RIS="$RIS ${!CONTO}"
done

echo $RIS

./script2.sh ${RIS}
