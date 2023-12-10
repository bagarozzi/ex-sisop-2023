set -a

PIPPO="ciao"

env | grep PIPPO=ciao && echo "La variabile è diventata di ambiente"

set +a 

unset PIPPO
