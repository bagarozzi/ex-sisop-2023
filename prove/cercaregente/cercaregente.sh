#!/bin/bash
actualname=""
for name in `find .. -type f -name "*.h" -mindepth 2 -print` ; do
    if [[ ${actualname} == "" ]] ; then actualname=${name} ; fi
    if [[ ${actualname} -ot ${name} ]] ; then 
        actualname=${name};
    fi
done

echo "Most recent file: ${actualname}"