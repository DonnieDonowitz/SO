#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define DIM 100
typedef struct threadargs{
	int id;
	char filein[200];
	char fileout[200];
}ta;
int** global_matrix;
int* thread_global;

int* read_file(char*,int*);
void write_file(char*,int*,int);
void *thread(ta* t);
void sort(int*,int);
int merge(int*,int*,int*,int,int,int);
void main(int argc, char** argv){
	pthread_t* tid;
	ta* t;
	int nT;
	nT=atoi(argv[1]);

	tid=(pthread_t*)malloc(nT*sizeof(pthread_t));
	thread_global=(int*)malloc(nT*sizeof(int));
	for(int tr=0;tr<nT;++tr) thread_global[tr]=0;
	global_matrix=(int**)malloc(nT*sizeof(int*));
	for(int tm=0;tm<nT;++tm) global_matrix[tm]=(int*)malloc(DIM*sizeof(int));
	for(int row=0;row<nT;++row){
		for(int col=0;col<DIM;++col) global_matrix[row][col]=0;
	}
	for(int i=0;i<nT;++i){
		t=(ta*) malloc(sizeof(ta));
		t->id=i;
		sprintf(t->filein,"%s%d",argv[2],i+1);
		sprintf(t->fileout,"%s",argv[3]);
		pthread_create(&tid[i],NULL,(void *) thread,t);
	}
	int* merged_vector;
	int tt=0,start=0;
	merged_vector=(int *) malloc((DIM*nT)*sizeof(int));
	for(int j=0;j<(DIM*nT);++j) merged_vector[j]=0;
	for(int done=0;done<nT;done++){
		if(thread_global[tt]==1){
			thread_global[tt]=0;
			int* vtmp=(int* )malloc((DIM*nT)*sizeof(int));
			for(int m=0;m<(DIM*nT);++m) vtmp[m]=merged_vector[m];
			start=merge(global_matrix[tt],vtmp,merged_vector,global_matrix[tt][0],DIM*nT,start);
			free(vtmp);
		}
		tt++;
		tt%=nT;
		sleep(1);
	}
	write_file(argv[3],merged_vector,start);
	free(merged_vector);
	for(int i=0;i<nT;++i) free(global_matrix[i]);
	free(global_matrix);
	free(t);
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
	for(int i=0;i<size;++i) fprintf(fp,"%d\n",vet[i]);
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
	global_matrix[t->id][0]=size;
	for(int i=1;i<=size;++i){
		global_matrix[t->id][i]=vet[i-1];
	}	
	thread_global[t->id]=1;
	free(vet);
	pthread_exit(NULL);
}
int merge(int* v1,int* v2,int* merged,int size1,int size2,int start){
	for(int i=0;i<size1;++i) merged[start+i]=v1[i];
	for(int j=0;j<size2;++j) merged[start+size1+j]=v2[j];
	return size1+size2+start;
}	
