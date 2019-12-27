#!/bin/bash

if test $# -ne 3; then
	echo "Usage: ./scriptname dir func file"; exit 0
fi

if test ! -d $1; then
	echo "Not a directory"; exit 1
fi

grep -Hnr "$2 *(.*)" $1 | sort -t ':' -k 1 -k 2rn > $3
