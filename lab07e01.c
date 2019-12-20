#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void binary(int*,int);

int main(int argc,char** argv){
	int n,*vet;
	
	n=atoi(argv[1]);
	vet=(int *) malloc(n*sizeof(int));
	
	if(vet==NULL){
		fprintf(stderr,"Error while allocating vector!\n");
		exit(0);
	}
	
	printf("Binary Nums:\n");
	binary(vet,n);
	free(vet);
	
	return 0;
}

void binary(int* vet,int n){
	for(int i=0;i<=n;++i){
		if(i==n){
			for(int j=0;j<n;++j)	printf("%d",vet[j]);
			printf("\n");
			exit(0);
		}else{
			if(fork()==0){
				vet[i]=0;
			}else{
				if(fork()==0){
					vet[i]=1;
				}else{
					wait(NULL);
					wait(NULL);
					exit(1);
				}
			}
		}
	}
	exit(0);
}
