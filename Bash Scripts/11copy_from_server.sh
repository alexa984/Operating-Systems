#!/bin/bash
if [ $# -ne 1 ]
then
	echo "you should pass one argument"
	exit 1
fi
scp s62229@62.44.100.23:"${1}" .

