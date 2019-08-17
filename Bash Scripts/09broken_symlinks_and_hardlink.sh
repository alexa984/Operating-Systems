#!/bin/bash
if [ ! -d "${1}" ]
then
	echo 'Invalid argument passed'
	exit 1
fi

if [ -z "${2}" ]
then
	#find all broken symlinks 
	find -L "${1}" -type l
	exit 2
fi

for i in $(find "${1}" -type f)
do
	if [ $(stat -c '%h' "${i}") -ge $2 ]
	then
		echo "${i}"
	fi
done
