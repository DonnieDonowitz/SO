#!/bin/bash

if test $# -ne 1; then
	echo "Usage: ./scriptname file"; exit 0
fi
words=()
h=0
freq=()
for wd in 'cat $1'; do
	found=0
	for ((i=0; i<${words[*]}; i++))
	do
		if [ "$wd" == "$words[$i]"]
		then
			freq[$i]=$((freq[$i]+1))
			found=1
		fi 
	done
	if [ $found -eq 0]
	then
		words[$h]=$wd
		freq[$h]=1
		h=$(($h+1))
	fi
done

for((i=0;i<${words[*]};i++))
do
	echo ${words[$i]} "-" ${freq[$i]}
done

