CONTATORE=0
ARGOMENTI=""

for  (( CONTATORE=1 ; CONTATORE<=$# ; CONTATORE=${CONTATORE}+1 )) ; do
	ARGOMENTI="${ARGOMENTI} ${!CONTATORE}"
done

./stampaargs.sh $# "$@"
