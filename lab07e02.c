#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct threadargs{
	char filein[200];
	char fileout[200];
}ta;


int* read_file(char*,int*);
void write_file(char*,int*,int);
void *thread(ta* t);
void sort(int*,int);
void main(int argc, char** argv){
	pthread_t tid;
	ta* t;
	int nT;
	
	nT=atoi(argv[1]);
	for(int i=0;i<nT;++i){
		t=(ta*) malloc(sizeof(ta));
		sprintf(t->filein,"%s%d",argv[2],i+1);
		sprintf(t->fileout,"%s%d",argv[3],i+1);
		pthread_create(&tid,NULL,(void *) thread,t);
		pthread_join(tid,NULL);
	}
	return;
}

int* read_file(char* file,int* size){
	FILE* fp;
	int* vet;
	
	fp=fopen(file,"r");
	fscanf(fp,"%d",&(*size));
	vet=(int*) malloc((*size)*sizeof(int));
	for(int i=0;i<*size;++i) fscanf(fp,"%d",&vet[i]);
	fclose(fp);
	return vet;
}

void write_file(char* file,int* vet,int size){
	FILE* fp;
	
	fp=fopen(file,"w");
	for(int i=0;i<size;++i) fprintf(fp,"%d",vet[i]);
	fclose(fp);
	return ;
}

void sort(int* v,int size){
	int tmp;
	
	for(int i=0;i<size;++i){
		for(int j=0;j<i;++j){
			if(v[i]>v[j]){
				tmp=v[j];
				v[j]=v[i];
				v[i]=tmp;
			}
		}	
	}
	return;
}

void *thread(ta* t){
	int size;
	int* vet;
	
	vet=read_file(t->filein,&size);
	sort(vet,size);
	write_file(t->fileout,vet,size);
	
	exit(0);
}
		
	
		
