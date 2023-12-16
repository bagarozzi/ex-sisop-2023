#!/bin/bash
# separanomi.sh

for name in `echo ${PATH} | sed 's/://g' | sed 's/\// /g'` ; do echo -n "${name} " ; done