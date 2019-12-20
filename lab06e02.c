#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void father(int fd1[2],int fd2[2]);
int child(int fd1[2],int fd2[2]);

void main(void){
	int fd1[2],fd2[2];
	
	pipe(fd1);
	pipe(fd2);
	
	if(fork()==0)
		child(fd1,fd2);
	else{
		father(fd1,fd2);
	}
	wait(NULL);
return;
}

void father(int fd1[2],int fd2[2]){
	char c[1];
	int i=0;
	close(fd2[1]);
	close(fd1[0]);
	
	while(i<10){
		fprintf(stdout,"I'm the father(PID=%d)\n",getpid());
		sprintf(c,"C");
		write(fd1[1],c,1);
		i++;
		read(fd2[0],c,1);
	}
	write(fd1[1],"F",1);
	close(fd2[0]);
	close(fd1[1]);
}

int child(int fd1[2],int fd2[2]){
	char c[1];
	
	close(fd2[0]);
	close(fd1[1]);
	
	while(1){
		read(fd1[0],c,1);
		if(strcmp(c,"C")==0) fprintf(stdout,"I'm the child(PID=%d)\n",getpid());
		else if(strcmp(c,"F")==0){
			close(fd2[1]);
			close(fd1[0]);
			exit(1);
		}
		sprintf(c,"F");
		write(fd2[1],c,1);
	}
}
