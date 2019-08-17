#!/bin/bash

CNT=0

while read FILE; do
	CNT=$(($CNT + 1))
done < <(find ~ -maxdepth 1)

echo "counter: ${CNT}"
