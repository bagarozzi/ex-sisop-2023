export ARGOMENTI=""

for name in "$@" ; do ARGOMENTI="${ARGOMENTI} ${name}" ; done

./stampaargs2.sh "$ARGOMENTI"
