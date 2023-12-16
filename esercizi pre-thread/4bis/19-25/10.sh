for filename in `ls` ; do 
echo "File is ${filename}"
echo "File props: `ls -ld $filename`"
done 
