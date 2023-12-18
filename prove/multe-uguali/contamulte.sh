#!/bin/bash
# eseguire con ./contamulte.sh < multe.txt

read NOME COGNOME SOLDI GIORNO MESE ANNO # la prima riga la faccio prima del while
SOLDIATTUALI=${SOLDI}
OCCORRENZE=1


while read NOME COGNOME SOLDI GIORNE MESE ANNO ; do 
    if [[ ${SOLDIATTUALI} == ${SOLDI} ]] ; then 
        (( OCCORRENZE=${OCCORRENZE}+1 )); # se c'è un altro valore uguale continuo a contare
    else 
        echo "${SOLDIATTUALI} ${OCCORRENZE}"
        SOLDIATTUALI=${SOLDI}  # se i valori sono finiti, stampo ed inizio a tenere traccia del nuovo valore
        OCCORRENZE=1
    fi
done

# devo fare un ultimo controllo fuori dal while perché la read fallisce la condizione sull'ultima lettura che fa

if [[ ${SOLDIATTUALI} == ${SOLDI} ]] ; then 
    (( OCCORRENZE=${OCCORRENZE}+1 ));
else 
    echo "${SOLDIATTUALI} ${OCCORRENZE}"
    SOLDIATTUALI=${SOLDI} 
    OCCORRENZE=1
fi

# tengo anche else perchè se alla fine ci sono due valori diversi li stampa comunque (nell'esempio ci sono due mille)

echo "$SOLDIATTUALI $OCCORRENZE" 