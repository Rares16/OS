checkc=0
if test -f $1
then 

echo `gcc -Wall "$1" 2>&1| egrep 'error:' | wc -l`
echo `gcc -Wall "$1" 2>&1| egrep 'warning:' | wc -l`


else echo "Not a File"
fi
