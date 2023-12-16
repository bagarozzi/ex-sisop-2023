#!/bin/bash
# cercafile.sh

for filename in /usr/lib/?{c..g}* ; do
    if [[ -e ${name} && ( ${#filename} -ge 18 || ${#filename} -le 23 ) ]] ; then
        echo "/usr/include/${filename}"
    fi
done