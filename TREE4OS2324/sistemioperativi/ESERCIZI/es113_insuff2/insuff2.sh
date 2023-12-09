#!/bin/bash

while read NOME COGNOME MATRICOLA VOTO ; do
	if (( ${VOTO} < "18" )) ; then
		LINES=`grep ${MATRICOLA} RisultatiProvaPratica1.txt | wc -l`
		if [[ "${LINES}" == "0" ]] ; then 
			echo ${COGNOME} ${MATRICOLA} ${NOME} ${COGNOME} ${VOTO}
		fi
	fi
# done < RisultatiProvaPratica2.txt
done < RisultatiProvaPratica2.txt | sort | cut -d ' ' -f2-

