#!/bin/bash

for name in `find /usr/include/ -type f` ; do
    head -n 3 ${name}
done | cut -b 3