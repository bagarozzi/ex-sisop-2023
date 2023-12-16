for (( CONTATORE=1 ; CONTATORE<=$# ; CONTATORE=${CONTATORE}+1 )) ; do
	echo "${!CONTATORE}"
done
