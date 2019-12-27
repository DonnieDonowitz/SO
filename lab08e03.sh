#!/bin/bash

if test $# -ne 1; then
	echo "Usage: ./scriptname dir"; exit 0
fi
if test ! -d $1; then 
	echo "Not a directory"; exit 1
fi
for x in 'ls -laR $1'; do
	mv $1/$x $1/'echo $x | tr A-Z a-z'
done