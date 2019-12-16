#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N 132

int sender(pid_t pid,int fd[2]);
int receiver(int fd[2]);

void main(void){
	pid_t pid1,pid2;
	int fd[2];
	
	pipe(fd);
	
	pid1=fork();
	if(pid1==0){
		receiver(fd);
	}else{
		pid2=fork();
		if(pid2==0){
			sender(pid1,fd);
		}
	}
	wait(NULL);
	wait(NULL);
	
	return;
}

int sender(pid_t pid,int fd[2]){
	char line[N],fullLine[N+6];
	int sentMsg=0;
	close(fd[0]);
	while(1){
		scanf("%s",line);
		sprintf(fullLine,"%6d%s",getpid(),line);
		write(fd[1],fullLine,N+6);
		if(strcmp(line,"end")==0) break;
		sentMsg++;
	}
	exit(sentMsg);
}

int receiver(int fd[2]){
	char line[N],fullLine[N+6];
	int receivedMsg=0;
	pid_t senderPid;
	close(fd[1]);
	while(1){
		read(fd[0],fullLine,N+6);
		sscanf(fullLine,"%6d%s",&senderPid,line);
		if(strcmp(line,"end")==0) break;
		for(int i=0;i<strlen(line);++i) line[i]=toupper(line[i]);
		fprintf(stdout,"%s\t",line);
		fflush(stdout);
		receivedMsg++;
	}
	exit(receivedMsg);
}
