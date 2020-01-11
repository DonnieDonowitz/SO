#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semA,semB,semC,semD,semE,semF,semG,semH,semI;
pthread_t tidA,tidB,tidC,tidD,tidE,tidF,tidG,tidH,tidI;

void* pA(void* arg){
	while(1){
		sem_wait(&semA);
		fprintf(stdout,"A\n");
		sem_post(&semB);
		sem_post(&semC);
		sem_post(&semD);
	}
}
void* pB(void* arg){
	while(1){
		sem_wait(&semB);
		fprintf(stdout,"B\n");
		sem_post(&semI);
	}
}
void* pC(void* arg){
	while(1){
		sem_wait(&semC);
		fprintf(stdout,"C\n");
		sem_post(&semE);
		sem_post(&semF);
	}
}
void* pD(void* arg){
	while(1){
		sem_wait(&semD);
		fprintf(stdout, "D\n");
		sem_post(&semH);
	}
}
void* pE(void* arg){
	while(1){
		sem_wait(&semE);
		fprintf(stdout,"E\n");
		sem_post(&semG);
	}
}
void* pF(void* arg){
	while(1){
		sem_wait(&semF);
		fprintf(stdout,"F\n");
		sem_post(&semG);
	}
}
void* pG(void* arg){
	while(1){
		sem_wait(&semG);
		sem_wait(&semG);
		fprintf(stdout,"G\n");
		sem_post(&semI);
	}
}
void* pH(void* arg){
	while(1){
		sem_wait(&semH);
		fprintf(stdout,"H\n");
		sem_post(&semI);
	}
}
void* pI(void* arg){
	while(1){
		sem_wait(&semI);
		sem_wait(&semI);
		sem_wait(&semI);
		fprintf(stdout,"I\n");
		sem_post(&semA);
	}
}

void main(void) {
	sem_init(&semA,0,1);
	sem_init(&semB,0,0);
	sem_init(&semC,0,0);
	sem_init(&semD,0,0);
	sem_init(&semE,0,0);
	sem_init(&semF,0,0);
	sem_init(&semG,0,0);
	sem_init(&semH,0,0);
	sem_init(&semI,0,0);

	pthread_create(&tidA,NULL,pA,NULL);
	pthread_create(&tidB,NULL,pB,NULL);
	pthread_create(&tidC,NULL,pC,NULL);
	pthread_create(&tidD,NULL,pD,NULL);
	pthread_create(&tidE,NULL,pE,NULL);
	pthread_create(&tidF,NULL,pF,NULL);
	pthread_create(&tidG,NULL,pG,NULL);
	pthread_create(&tidH,NULL,pH,NULL);
	pthread_create(&tidI,NULL,pI,NULL);

	sem_destroy(&semA);
	sem_destroy(&semB);
	sem_destroy(&semC);
	sem_destroy(&semD);
	sem_destroy(&semE);
	sem_destroy(&semF);
	sem_destroy(&semG);
	sem_destroy(&semH);
	sem_destroy(&semI);

	return;
}
