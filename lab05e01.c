#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char** argv){
	int num;
	while(fscanf(stdin,"%d",&num)!=EOF){
		if(num==0) exit(0);
		else if(num%2==0) fprintf(stdout,"%d  ",num);
		else fprintf(stderr,"%d  ",num);
	}
	return 0;
}
