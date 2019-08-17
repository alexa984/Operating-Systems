#!/bin/bash
max_depth=0
curr_depth=0
if [ ! -f $1 ]
then
	echo 'The given file does not exist'
	exit 1
fi

for word in $(cat $1)
do
	if [ $word = '{' ]
	then 
		((curr_depth++))
		if [ $curr_depth -gt $max_depth ]
		then      
			max_depth=$curr_depth
		fi
	elif [ $word = '}' ]
	then
		((curr_depth--))
	fi
done
echo "The deepest nesting is $max_depth levels"

