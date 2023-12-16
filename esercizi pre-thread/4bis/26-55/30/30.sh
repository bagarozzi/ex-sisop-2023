cut -b 3-5,10-15 fileditesto.txt | sed 's/ //g' | sed 's/*//g' | wc -c 

# versione del comando 28 che usa stream editor per rimuvoere asterischi e spazi al suo output e contarne i caratteri