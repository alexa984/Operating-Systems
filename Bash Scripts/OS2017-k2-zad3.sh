#!/bin/bash

# Задача 3.
# Напишете скрипт, който ако се изпълнява от root потребителя:
# а) извежда обобщена информация за броя и общото количество активна памет (RSS - resident set
# size, non-swaped physical memory that a task has used) на текущите процеси на всеки потребител;
# б) ако процесът с най-голяма активна памет на даден потребител използва два пъти повече памет
# от средното за потребителя, то скриптът да прекратява изпълнението му по подходящ начин.


if [ $(id -u) -ne 0 ]; then
	echo "Script should be run by root"
	exit 1
fi

users=$(ps -e -o user | sort | uniq )
rss_total=0
for user in $users; do
	num_processes_for_this_user=0
	total_rss=0
	pid_of_process_with_max_rss=0
	max_rss=0

	while read upid urss; do
		total_rss=$(( ${total_rss} + $urss ))
		if [ $urss -gt $max_rss ]; then
			max_rss=$urss
			pid_of_process_with_max_rss=$upid
		fi
		num_processes_for_this_user=$(( ${num_processes_for_this_user} + 1 ))

	done< <(ps -e --no-headers -u $user -o pid= -o rss=)
	
	echo "All used RSS for user $user is ${total_rss}."

	average=$(( ${total_rss} / ${num_processes_for_this_user} ))
	if [ ${max_rss} -ge $(( 2 * ${average} )) ]; then
		echo "Process with id ${pid_of_process_with_max_rss} will be killed"
		kill -s SIGTERM ${pid_of_process_with_max_rss}
		sleep 2
		kill -s SIGKILL ${pid_of_process_with_max_rss}
	fi
done

