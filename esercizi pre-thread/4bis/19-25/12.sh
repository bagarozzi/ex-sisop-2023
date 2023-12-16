for filename in `ls || echo "ls produce errore" ; exit 0` ; do echo -e "File is: ${filename}\nFile props: `ls -ld ${filename}`" ; done
