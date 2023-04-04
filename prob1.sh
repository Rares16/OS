if test $# -lt 2

then echo "It has at least 2 arguments"
exit 1
else echo "More the 2 arguments"

fi

if test -f $1

then echo "First arg is a file"
else echo "First arg is not a file"

fi
sum=0
argg=$2
for argg
do
    if test $argg = $1
    then continue
    else
    sum=`expr $sum + $argg`
    fi
done

if test $((sum%2)) -eq 0
then echo "The result is an odd number" > $1
else date +"%H:%M"
fi
