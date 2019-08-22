#!/bin/bash

# Задача 1. Напишете скрипт, който извежда името на потребителския акаунт, в чиято home дирек-
# тория има най-скоро променен обикновен файл и кой е този файл. Напишете скрипта с подходящите
# проверки, така че да бъде валиден администраторски инструмент.

while read usr home_dir; do
    if [ -d ${home_dir} ]; then
        find ${home_dir} -type f -printf "${usr} %p %T@\n" 2>/dev/null
    fi
done< <(cat /etc/passwd | cut -d ':' -f 1,6 | tr ':' ' ') | sort -k3 -n | tail -n 1 | cut -d 1,2
