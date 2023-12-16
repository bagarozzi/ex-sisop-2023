#!/bin/bash
# cercadir.sh usando la forma "test"

# si potrebbe fare one liner così find /usr/lib -type d -maxdepth 1 -perm +w -newer /usr/incl/stdio.h

for filename in /usr/lib/* ; do
    if test -d ${filename} -a -r ${filename} -a filename -nt /usr/include/stdio.h ; then
        echo "/usr/include/${filename}"
    fi
done