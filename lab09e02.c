#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int* sem;

sem semA,semBCD,semEF,semG,semH,semI;

sem sem_create(){
	sem s;
	s=calloc(2,sizeof(int));
	pipe(s);
	return s;
}

void sem_wait(sem s){
	int n;
	if(read(s[0],&n,1)<=0){
		fprintf(stderr,"Error: wait! \n");
		exit(1);
	}
}

void sem_signal(sem s){
	if(write(s[1],"x",1)<=0){
		fprintf(stderr,"Error: signal! \n");
		exit(2);
	}
}

void pA(){
	sem_wait(semA);
	sleep(1);
	fprintf(stdout,"A\n");
	sem_signal(semBCD);
	sem_signal(semBCD);
	sem_signal(semBCD);
	exit(0);
}
void pB(){
	sem_wait(semBCD);
	sleep(2);
	fprintf(stdout,"B\n");
	sem_signal(semI);
	exit(0);
}
void pC(){
	sem_wait(semBCD);
	sleep(3);
	fprintf(stdout,"C\n");
	sem_signal(semEF);
	sem_signal(semEF);
	exit(0);
}
void pD(){
	sem_wait(semBCD);
	sleep(4);
	fprintf(stdout, "D\n");
	sem_signal(semH);
	exit(0);
}
void pE(){
	sem_wait(semEF);
	sleep(1);
	fprintf(stdout, "E\n");
	sem_signal(semG);
	exit(0);
}
void pF(){
	sem_wait(semEF);
	sleep(2);
	fprintf(stdout,"F\n");
	sem_signal(semG);
	exit(0);
}
void pG(){
	sem_wait(semG);
	sem_wait(semG);
	sleep(1);
	fprintf(stdout,"G\n");
	sem_signal(semI);
	exit(0);
}
void pH(){
	sem_wait(semH);
	sleep(5);
	fprintf(stdout,"H\n");
	sem_signal(semI);
	exit(0);
}
void pI(){
	sem_wait(semI);
	sem_wait(semI);
	sem_wait(semI);
	sleep(1);
	fprintf(stdout,"I\n");
	sem_signal(semA);
	exit(0);
}

void main(void){
	int pidA,pidB,pidC,pidD,pidE,pidF,pidG,pidH;

	semA=sem_create();
	semBCD=sem_create();
	semEF=sem_create();
	semG=sem_create();
	semH=sem_create();
	semI=sem_create();

	sem_signal(semA);

	while(1){
		pidA=fork();
		if(pidA!=0){
			pidB=fork();
			if(pidB!=0){
				pidC=fork();
				if(pidC!=0){
					pidD=fork();
					if(pidD!=0){
						pidH=fork();
						if(pidH!=0)	pI();
						else pH;
					}
				}else{
					pidE=fork();
					if(pidE!=0){
						pidF=fork();
						if(pidF!=0)	pF();
						else pE();
					}else pC();
				}
			}else pB();
		}else pA();
	}

}