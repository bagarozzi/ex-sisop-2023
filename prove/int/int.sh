#!/bin/bash

# `find -type f -name "*.h" /usr/include/linux/`

for name in `find . -type f -name "*.txt"` ; do 
    while read str ; do 
        LINE=`echo ${str} | grep "int"`
        if [[ LINE!=" " || LINE!="" ]] ; then 
            echo `echo ${LINE} | head -c 3`
        fi
    done < ${name}
    LINE=`echo ${str} | grep "int"`
    if [[ -n LINE ]] ; then 
        echo `echo ${LINE} | head -c 3`
    fi
done