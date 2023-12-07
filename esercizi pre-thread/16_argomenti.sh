#!/bin/bash

STRINGA=""
COUNT=0

while [[ ${COUNT} != $# ]] ; do 
	(( COUNT=${COUNT}*2 + 1 ))
	STRINGA=${STRINGA}${!COUNT}"" ; done

echo $STRINGA
