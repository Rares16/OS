score=0
if test -f $1
then 

score=`gcc -Wall "$1" 2>&1| egrep 'error:|warning:' | wc -l`
echo "For the file $1 there is $score warnings/errors"

else echo "Not a Directory"
fi
