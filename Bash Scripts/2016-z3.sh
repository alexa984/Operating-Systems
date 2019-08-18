#!/bin/bash
if [ $# -ne 2 ]; then
	echo "You should provide two arguments"
	exit 1
fi

if ! [[ $1~='^[0-9]+$' ]]; then
	echo "First argument should be a number"
	exit 2
fi

if ! [[ $2~='^[0-9]+$' ]]; then
        echo "Second argument should be a number"
	exit 2
fi

mkdir a b c
while read file; do
	lines=$(cat $file | wc -l)
	if [ $lines -lt $1 ]; then
		mv $file a
	elif [ $lines -le $2 ]; then
		mv $file b
	else
		mv $file c
	fi
done < <(find -maxdepth 1 -type f ) 
