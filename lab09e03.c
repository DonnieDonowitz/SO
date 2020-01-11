#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t semA,semBCD,semEF,semG,semH,semI;
pthread_t tidA,tidB,tidC,tidD,tidE,tidF,tidG,tidH,tidI;

void* pA(void* arg){
	sem_wait(&semA);
	fprintf(stdout,"A\n");
	for(int i=0;i<3;++i) sem_post(&semBCD);
	return NULL;
}
void* pB(void* arg){
	sem_wait(&semBCD);
	fprintf(stdout,"B\n");
	sem_post(&semI);
	return NULL;
}
void* pC(void* arg){
	sem_wait(&semBCD);
	fprintf(stdout,"C\n");
	for(int i=0;i<2;++i) sem_post(&semEF);
	return NULL;
}
void* pD(void* arg){
	sem_wait(&semBCD);
	fprintf(stdout, "D\n");
	sem_post(&semH);
	return NULL;
}
void* pE(void* arg){
	sem_wait(&semEF);
	fprintf(stdout,"E\n");
	sem_post(&semG);
	return NULL;
}
void* pF(void* arg){
	sem_wait(&semEF);
	fprintf(stdout,"F\n");
	sem_post(&semG);
	return NULL;
}
void* pG(void* arg){
	for(int i=0;i<2;++i) sem_wait(&semG);
	fprintf(stdout,"G\n");
	sem_post(&semI);
	return NULL;
}
void* pH(void* arg){
	sem_wait(&semH);
	fprintf(stdout,"H\n");
	sem_post(&semI);
	return NULL;
}
void* pI(void* arg){
	for(int i=0;i<3;++i) sem_wait(&semI);
	fprintf(stdout,"I\n");
	sem_post(&semA);
	return NULL;
}

void main(void) {
	sem_init(&semA,0,1);
	sem_init(&semBCD,0,0);
	sem_init(&semEF,0,0);
	sem_init(&semG,0,0);
	sem_init(&semH,0,0);
	sem_init(&semI,0,0);

	while(1){
		pthread_create(&tidA,NULL,pA,NULL);
		pthread_create(&tidB,NULL,pB,NULL);
		pthread_create(&tidC,NULL,pC,NULL);
		pthread_create(&tidD,NULL,pD,NULL);
		pthread_create(&tidE,NULL,pE,NULL);
		pthread_create(&tidF,NULL,pF,NULL);
		pthread_create(&tidG,NULL,pG,NULL);
		pthread_create(&tidH,NULL,pH,NULL);
		pthread_create(&tidI,NULL,pI,NULL);
	}

	sem_destroy(&semA);
	sem_destroy(&semBCD);
	sem_destroy(&semEF);
	sem_destroy(&semG);
	sem_destroy(&semH);
	sem_destroy(&semI);
	return;
}
