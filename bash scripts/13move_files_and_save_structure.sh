#!/bin/bash
if [ $# -ne 3 ]; then
	echo 'you should pass three arguments to this script'
	exit 1
fi
if [ ! -d $1 ]; then
	echo 'arg1 must be a directory'
	exit 2
fi
if [ ! -d $2 ]; then
	echo 'arg2 must be a directory'
	exit 3
fi
if [ "$(find $2 -type f)" ]; then
	echo 'arg2 directory must be empty'
	exit 4
fi
if [ ! $USER==root ]; then
	echo "script must be run by root, $USER"
fi
SRC=$1
DST=$2
ABC=$3
while read file; do
	#move file
	dest_file=$(echo $file | sed -e "s/${SRC}/${DST}/")
	mkdir -p $(dirname $dest_file)
	mv $file $dest_file
done < <(find $SRC -type f -name "*$ABC*")
