#!/bin/bash

# Задача 2. Напишете скрипт, който приема три задължителни позицонни аргумента:
# • име на фаил
# • низ1
# • низ2
# Файлът е текстови, и съдържа редове във формат:
# ключ=стойност
# където стойност може да бъде:
# • празен низ, т.е. редът е ключ=
# • низ, състоящ се от един или повече термове, разделени с интервали, т.е., редът е ключ=t 1 t 2 t 3
# Някъде във файла:
# • се съдържа един ред с ключ първия подаден низ (низ1 );
# • и може да се съдържа един ред с ключ втория подаден низ (низ2 ).
# Скриптът трябва да променя реда с ключ низ2 така, че обединението на термовете на редовете с
# ключове низ1 и низ2 да включва всеки терм еднократно.

if [ $# -ne 3 ]; then
	echo "You should provide 3 arguments"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "First argument should be a valid file name"
	exit 2
fi

while read line; do
	key=$(echo $line | cut -d '=' -f 1)
	values=$(echo $line | cut -d '=' -f 2)
	if [ $key == $2 ]; then
		str1_terms=$values
	fi
	if [ $key == $3 ]; then
		str2_terms=$values
	fi
done< <(cat $1)

all_terms=$(echo "$str1_terms $str2_terms")
unique_terms=$(echo $all_terms | tr ' ' '\n' | sort | uniq)
needed_terms=''
for term in $unique_terms; do
	if [[ -z $(echo ${str1_terms} | grep $term) ]]; then
		needed_terms=$(echo "${needed_terms} ${term}")
	fi
done

#remove trailing whitespace
needed_terms="${needed_terms:1}"

sed -i -e "s|\(${3}=\)\(.*\)|\1${needed_terms}|" $1
