#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N 132
#define NAME "tmp.txt"

void sigHand(int sig){
	return;
}

int receiver();
int sender(pid_t receiverPid);

void main(void){
	pid_t pid1,pid2;
	signal(SIGUSR1,sigHand);
	pid1=fork();
	if(pid1==0){
		receiver();
	}else{
		pid2=fork();
		if(pid2==0){
			sender(pid1);
		}
	}
	wait(NULL);
	wait(NULL);
	return;
}

int sender(pid_t receiverPid){
	int sentMsg=0;
	char line[N];
	FILE* fp;
	while(1){
		fp=fopen(NAME,"w");
		fscanf(stdin,"%s",line);
		fprintf(fp,"%d %s", getpid(),line);
		fclose(fp);
		sentMsg++;
		kill(receiverPid,SIGUSR1);
		if(strcmp(line,"end")==0) break;
		pause();
	}
	exit(sentMsg);
}

int receiver(){
	FILE* fp;
	char line[N];
	int receivedMsg=0;
	pid_t senderPid;
	while(1){
		pause();
		sleep(1);
		fp=fopen(NAME,"r");
		fscanf(fp,"%d %s",&senderPid,line);
		fclose(fp);
		if(strcmp(line,"end")==0) break;
		for(int i=0;i<strlen(line);++i) line[i]=toupper(line[i]);
		fprintf(stdout,line);
		receivedMsg++;
		kill(senderPid,SIGUSR1);
	}
	exit(receivedMsg);
}
