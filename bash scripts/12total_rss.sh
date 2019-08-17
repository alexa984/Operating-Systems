#!/bin/bash
#second task 2016
if [ $USER != "root" ]; then
	echo "you are not root, $USER. Bye!"
	exit 1
fi

users=$(ps -e -o user | sort | uniq)
for user in $users
do
	read total_rss< <( ps -e -o uid=$user,pid,rss --no-headers | awk '{sum+=$3}END{print sum}')
	echo "$user $total_rss"
	if [[ $1 -le $total_rss ]]; then
		echo "should stop process with max rss"
	fi
done
