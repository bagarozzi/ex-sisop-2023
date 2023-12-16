for (( CONTATORE=10 ; CONTATORE>0 ; CONTATORE=${CONTATORE}-1 )) ; do
    ./../51.sh 10 1>&2 &
    echo -n "$! "
done

