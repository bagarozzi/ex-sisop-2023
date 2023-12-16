#!/bin/bash
# triplette.sh

for fileX in `find . -type f -maxdepth 1` ; do 
    for fileY in `find . -type f -maxdepth 1` ; do
        for fileX in `find . -type f -maxdepth 1` ; do 
            echo "(${fileX};${fileY};${fileZ})"
        done
    done
done

# il prof diceva di cercare i file per questo ho fatto con find, però lui ha usato ls, ma ls da anche le directory
# dio cane