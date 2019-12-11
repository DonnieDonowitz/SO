#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
	int n=atoi(argv[1]),t=atoi(argv[2]);
	pid_t pid1,pid2;
	
	for(int i=0;i<n;i++){
		pid1=fork();
		if(pid1==0){
			//Child1
			//fprintf(stdout,"PID:%d   PPID:%d\n",getpid(),getppid());
		}else {
			pid2=fork();
			if(pid2==0){
				//Child2
				//fprintf(stdout,"PID:%d   PPID:%d\n",getpid(),getppid());
			}else{
				//Father
				//fprintf(stdout,"PID:%d   PPID:%d\n",getpid(),getppid());		
				exit(0);
			}
		}
	}
	
	sleep(t);
	fprintf(stdout," Leaf Process PID:%d   PPID:%d  and I slept %d seconds\n",getpid(),getppid(),t);
	return 0;
}
