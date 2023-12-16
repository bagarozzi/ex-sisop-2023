#!/bin/bash
# cercarecente.sh

MOSTRECENT=""
for name in `find /usr/include/linux -mindepth 2 -type f -name "*.h" -print` ; do
    if [[ MOSTRECENT=="" ]] ; then
        MOSTRECENT=${name};
    fi
    if [[ ${name} -nt ${MOSTRECENT} ]] ; then
        MOSTRECENT=${name}
    fi
done

echo "Most recent file: ${MOSTRECENT}"