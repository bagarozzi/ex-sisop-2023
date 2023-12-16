#!/bin/bash
# 41bis

# il prof grep -d skip '*' /usr/include/*
# però il prof non conta le righe, col suo comando basterebbe farlo due volte e metterlo in pipe con wc -l
# grep -d skip '*' /usr/include/* ; grep -d skip '*' /usr/include/* | wc -l

# io
CONTATORE=0
for name in /usr/include/* ; do
    if [[ -f ${name} ]] ; then
    LINES=`grep '*' ${name}`
    echo "${LINES}"
    (( CONTATORE=${CONTATORE}+`grep -h -c '*' ${name}` ))
    fi
done

echo "Total lines found: ${CONTATORE}"

# in ogni modo, funzionano entrambi