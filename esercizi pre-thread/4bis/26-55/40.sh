#!/bin/bash
# dire se sto comando produce errori

for (( i=0; ls ./ ; i=i+1 )) ; do echo "${i}" ; done

# il problema è che c'è un errore sintattico nel for: dovrebbe esserci la command substitution con i backtick