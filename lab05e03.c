#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sigHand(int sig){
	return;
}

void child(pid_t pid){
	while(1){
		pause();
		fprintf(stdout,"Child woke up\n");
		sleep(2);
		kill(pid,SIGUSR1);
	}
	return;
}

void father(pid_t pid){
	while(1){
		sleep(2);
		kill(pid,SIGUSR1);
		pause();
		fprintf(stdout,"Father woke up\n");
	}
	return;
}

void main(void){
	pid_t pid;
	if(signal(SIGUSR1,sigHand) == SIG_ERR){
		fprintf(stderr,"Signal Handler Error. \n");
		return;
	}
	pid=fork();

	if(pid==0){
		child(getppid());
	}else{
		father(pid);
	}
	return;
}


