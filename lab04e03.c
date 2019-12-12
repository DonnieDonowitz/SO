#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX 257

int main(int argc,char** argv){
	FILE* fp;
	char cmd[MAX];
	
	fp=fopen(argv[1],"r");
	
	while(fgets(cmd,MAX,fp)!=NULL){
		system(cmd);
	}
	fclose(fp);
	return 0;	
}
