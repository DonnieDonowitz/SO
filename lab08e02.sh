#!/bin/bash

max=0
if test $# -ne 1 ; then
	echo "Insert file name: "; read 
	for row in 'cat $REPLY'
	do
		if($(wc -c row) -gt max)
			max=$(wc -c row)
		fi
	done
	echo '$max - $(wc -l $REPLY)'
else
	for row in 'cat $1'
	do
		if($(wc -c row) -gt max)
			max=$(wc -c row)
		fi
	done
	echo '$max - $(wc -l $1)'
fi

