trap "exit" SIGUSR2

./figlio.sh &

while true ; do echo "continuo a vivere" ; done