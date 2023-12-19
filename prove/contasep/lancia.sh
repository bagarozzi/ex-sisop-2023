#!/bin/bash

ARGOMENTI=`ls ./*.txt | head -n 3`

./contasep.sh "${ARGOMENTI}" 1>&2

#sia lo standard output che lo standard error di contaseparatamente.sh sullo standard error di lancia.sh stesso