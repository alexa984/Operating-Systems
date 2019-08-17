#!/bin/bash
#05-b-1800
if [ ! -f "${1}" ]; then
    echo "First argument must be a file"
    exit 1
fi

if [ ! -d "${2}" ]; then
    echo "Second argument must be a directory"
    exit 2
fi

find "${2}" -type f | while read FILE; do
    if [ $(md5sum "${FILE}" | cut -d ' ' -f 1) = $(md5sum "${1}" | cut -d ' ' -f 1) ]; then
        echo "${FILE}"
    fi
done


