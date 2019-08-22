#!/bin/bash

# Задача 1. Напишете скрипт, който получава задължителен първи позиционен параметър – ди-
# ректория и незадължителен втори – число. Скриптът трябва да проверява подадената директория
# и нейните под-директории и да извежда имената на:
# а) при подаден на скрипта втори параметър – всички файлове с брой hardlink-ове поне равен на
# параметъра;
# б) при липса на втори параметър – всички symlink-ове с несъществуващ destination (счупени
# symlink-ове).
# Забележка: За удобство приемаме, че ако има подаден втори параметър, то той е число.

if [ $# -lt 1 ]; then
	echo "You should provide at least 1 argument"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "First argument should be a directory"
	exit 2
fi

dir=$1

if [ ! -z $2 ]; then
	find $dir -type f -links +$2 2>/dev/null
else
	find -L $dir -type l 2>/dev/null
fi


### official solution:  ###

# check_dir() {
#	if [ ! -d "$1" ]; then
#		echo "$1 not a dir"
#		exit 2
#	fi
# }

# case $# in
#	1)
#	check_dir "$1"
#	find -L $1 -type l
#	;;
#	2)
#	check_dir "$1"
#	for i in $(find "$1" -type f); do
#		if [ $(stat -c ’%h’ "${i}") -ge $2 ]; then
#			echo "${i}"
#		fi
#	done
#	;;
#	*)
#	echo "usage: $0 <dirname> [<number>]"
# 	exit 1
# esac
