#!/bin/bash
# seleziona.sh

# avviare con cat file.txt | ./39.sh

while read RIGA ; do 
    RESULT=`echo ${RIGA} | grep A | wc -c`
    if (( ${RESULT}>0 )) ; then
    echo "${RESULT}"
    fi
done

# si poteva saltare tutta sta roba perché tanto grep va a righe già lui da solo con l'input che gli viene dato