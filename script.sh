score=0
if test -d $1
then for file in $1/*.c
do 

score=`gcc -Wall -o score $file 2>&1 | egrep 'error:|warning:' | wc -l`
echo "For the file $file there is $score warnings/errors " >> file.out

done

else echo "Not a Directory"
fi