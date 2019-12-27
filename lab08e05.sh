#!/bin/bash

if test $# -ne 2
then
	echo "Usage: ./scriptname process_name time_interval" ; exit 0
fi

zombie=0
while [ 1 -eq 1 ]; do
	line = 'ps -el | grep $1'

	if($? -eq 0)
		pid = 'cat line | cut -d ' ' -f 2'
		state = 'cat line | cut -d ' ' -f 9'

		if[ $state == "Z" ]
		then 
			zombie = $(($zombie+1))
		fi

		if [ $zombie -ge 5 ] 
		then
			kill -9 $pid
			echo "Process $pid killed successfully"
			exit 0
		else
			zombie = 0
		fi
	fi

	sleep $2

done

