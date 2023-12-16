for name in `find /usr/include/ -type f` ; do
    head -n 3 ${name}
done 