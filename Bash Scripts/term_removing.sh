#!/bin/bash
if [ $# -ne 3 ]
then
	echo 'you should pass three arguments'
fi
if [ ! -f "${1}" ]
then
	echo 'First argument should be a file'
fi
to_exclude=$2
cat $1 | while read l
do
	if [[ $l=~'$3=*' ]]
	then
		for ch in $l
		do
			if [[ $to_exclude~='*=*$ch*' ]]
			then
				echo 'im here'
				#remove this term
				echo "${l//$ch/}"	
			fi
		done
	fi
done
