#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void P368();
void P2457();

void main(void){
	fprintf(stdout,"P1   PID:%d   PPID:%d\n",getpid(),getppid());
	sleep(2);
	if(fork()){
		fprintf(stdout,"P2   PID:%d   PPID:%d\n",getpid(),getppid());
		sleep(2);
		P2457();
		wait(NULL);
	}else{
		fprintf(stdout,"P3   PID:%d   PPID:%d\n",getpid(),getppid());
		sleep(2);
		P368();
		exit(0);
	}
	fprintf(stdout,"P9   PID:%d   PPID:%d\n",getpid(),getppid());
	return;
}

void P368(){
	if(fork()){
		sleep(2);
		wait(NULL);
	}else{
		fprintf(stdout,"P6   PID:%d   PPID:%d\n",getpid(),getppid());
		sleep(2);
		exit(0);
	}
	fprintf(stdout,"P8   PID:%d   PPID:%d\n",getpid(),getppid());
	return;
}
void P2457(){
	if(fork()){
		fprintf(stdout,"P4   PID:%d   PPID:%d\n",getpid(),getppid());
		sleep(2);
		wait(NULL);
	}else{
		fprintf(stdout,"P5   PID:%d   PPID:%d\n",getpid(),getppid());
		sleep(2);
		exit(0);
	}
	fprintf(stdout,"P7   PID:%d   PPID:%d\n",getpid(),getppid());
	return;		
}
	
