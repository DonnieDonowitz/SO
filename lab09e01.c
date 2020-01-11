#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int ticketNumber;
int turnNumber;
int atomicIncrement(int *var){
	int tmp=*var;
	*var=tmp+1;
	return(tmp);
}

int init(){
	ticketNumber=0;
	turnNumber=0;
}

int unlock(){
	atomicIncrement(&turnNumber);
}

int lock(){
	int myturn = atomicIncrement(&ticketNumber);
	while(myturn != turnNumber);
}
