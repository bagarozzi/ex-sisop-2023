for name in `sudo find /usr -type f -name "*i.h" -maxdepth 3` ; do
    wc -l ${name}
done