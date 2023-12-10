for (( CONTATORE=$# ; CONTATORE>=1 ; CONTATORE=${CONTATORE}-1 )) ; do 
    echo ${!CONTATORE}
done
