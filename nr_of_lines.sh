if test -f $1 

then

echo "There are `wc -l "$1"` number of lines for $1"

else echo "Is not a file"

fi