#!/bin/bash
# cercadir.sh

# si potrebbe fare one liner così find /usr/lib -type d -maxdepth 1 -perm +w -newer /usr/incl/stdio.h

for filename in /usr/include/* ; do
    if [[ -d ${filename} && -r ${filename} && ${filename} -nt /usr/include/stdio.h ]] ; then
        echo "/usr/include/${filename}"
    fi
done