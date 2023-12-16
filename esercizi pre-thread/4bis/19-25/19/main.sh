#!/bin/bash

source definisci.sh # devo farlo con source se no va in un altra bash

./usa.sh

source elimina.sh

./usa.sh # Controllo che sia ancora

echo "fatto"