#!/bin/bash
if [ $# -ne 1 -o $(id -u) -ne 0 ]; then
	"Invalid number or arguments or missing permissions"
	exit 1
fi

users=$(ps -e --no-headers -o user | sort | uniq)

for user in $users; do
	tot_rss=$(ps -e -u $user -o rss= | awk '{sum += $1} END {print sum}')
	pid_max_rss=$(ps -e -u alexandra -o rss= -o pid= | sort -n | tail -n 1 | cut -d ' ' -f2)
	if [ $tot_rss -gt $1 ]; then
		echo "Killing process $pid_max_rss"
		kill -s SIGTERM $pid_max_rss
		sleep 3  # give the process some time to die
		kill -s SIGKILL $pid_max_rss  # kill it just to be sure
	fi
done
