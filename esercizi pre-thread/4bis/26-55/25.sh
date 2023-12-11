#!/bin/bash
# leggeretutto.sh
# come negli esempi delle slide ora devo controllare manualemente se read è arrivato alla fine del file

VAR=0
exec {FD}< ./miofileNoNL.txt
if (( $? == 0 )) ; then
    while read -u ${FD} RIGA ; do          
        if [[ $? == 0 && RIGA != ""]]
        then 
            echo "${RIGA}"
        else
            echo "End of file reached"
            break
        fi
    done
    exec {FD}>&-
fi