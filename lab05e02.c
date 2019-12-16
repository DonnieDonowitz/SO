#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define N 25

void sort(int,int);
int main(int argc,char** argv){
	int v,c;
	int fd;
	fd=creat(argv[1],0666);
	fd=open(argv[1],O_RDWR);
	
	if(fd==-1 || argc<2) {
		fprintf(stderr,"Error while opening file \n");
		exit(0);
	}
	
	int vet[N]={0,1,28,394,31,273,63,84,39,21,84,39,93,291,477,822,18,73,842,72,38,44,30,88,99};
	
	for(int i=0;i<N;++i) write(fd,&vet[i],sizeof(int));
	for(int i=0;i<N-1;++i){
		for(int j=0;j<N-1-i;++j){
			if(fork()){
				wait((int*) 0);
			}else{
				sort(fd,j);
				exit(0);
			}
		}
	}
	close(fd);
	
  fd = open (argv[1], O_RDONLY);
  if (fd == -1){
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    exit(-1);
  }

  fprintf (stdout, "File after  ordering    : ");
  for (int i=0; i<N; i++) {
    lseek (fd, i*sizeof (int), SEEK_SET);
    c = read (fd, &v, sizeof (int));
    if (c <= 0){
      fprintf (stderr, "Error reading file\n");
      exit (-1);
    }
    fprintf (stdout, "%2d ", v);
  }
  fprintf (stdout, "\n");

  close (fd);
	return 0;
}

void sort(int fd,int j){
	int v1,v2;
	
	lseek(fd,j*sizeof(int),SEEK_SET);
	read(fd,&v1,sizeof(int));
	read(fd,&v2,sizeof(int));
	if(v1>v2){
		lseek(fd,j*sizeof(int),SEEK_SET);
		write(fd,&v2,sizeof(int));
		write(fd,&v1,sizeof(int));
	}
	return;
}
