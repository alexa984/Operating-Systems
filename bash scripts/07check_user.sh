#!/bin/bash
if [[ "$USER" =~ [0-9]{5} ]]
then
	echo $USER
else
	echo "DANGER! It's a teacher!"
fi
