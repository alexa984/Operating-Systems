#!/bin/bash

# Задача 2. Напишете скрипт, който приема три задължителни позиционни параметра - директо-
# рия SRC, директория DST (която не трябва да съдържа файлове) и низ АBC. Ако скриптът се
# изпълнява от root потребителя, то той трябва да намира всички файлове в директорията SRC и
# нейните под-директории, които имат в името си като под-низ АBC, и да ги мести в директорията
# DST, запазвайки директорийната структура (но без да запазва мета-данни като собственик и права,
# т.е. не ни интересуват тези параметри на новите директории, които скриптът би генерирал в DST ).


if [ $# -ne 3 ]; then
	echo "You should provide 3 arguments"
	exit 1
fi

if [ ! -d $1 -o ! -d $2 ]; then
	echo "First 2 arguments should be directories."
	exit 2
fi

if [ ! -z "$(ls -A $2)" ]; then
	echo "DST directory should be empty!"
	exit 3
fi

if [ $(id -u) -eq 0 ]; then
	for file in $(find $1 -type f -name "*${3}*"); do
		dst=$(echo ${file} | sed -e "s/${1}/${2}/")
		mkdir -p $(dirname $dst)
		mv $file $dst
	done

fi

