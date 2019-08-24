#!/bin/bash
if [ $# -ne 2 ]; then
	echo "You should provide two arguments"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "First argument should be a directory"
	exit 2
fi

echo $(find $1 -maxdepth 1 -type f | grep "\<vmlinuz-[0-9]*\.[0-9]*\.[0-9]*-$2\>" | sort -n -t '-' -k2 | tail -n1)
