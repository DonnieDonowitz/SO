#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void recursive_ls (char* filename);
void main(int argc,char** argv){
	
	if(argc!=2){ fprintf(stderr," Error \n "); exit(1);}
	
	recursive_ls(argv[1]);
}

void recursive_ls (char* filename){
	DIR *dir;
	struct dirent *dirp;
	char fullname[257];
	struct stat sb;
	
	if(lstat(filename,&sb)<0) exit(5);
	if(S_ISDIR(sb.st_mode) == 0 ) return;
	dir=opendir(filename);
	if(dir==NULL) exit(4);
	while((dirp=readdir(dir))!=NULL){
		sprintf(fullname,"%s/%s",filename,dirp->d_name);
		if(lstat(fullname,&sb)<0) exit(5);
		if(S_ISDIR(sb.st_mode)==0){
			fprintf(stdout," Filename: %s    Path:%s\n",dirp->d_name,fullname);
		}else{
			fprintf(stdout," Filename: %s    Path:%s\n",dirp->d_name,fullname);
			if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0) recursive_ls(fullname);
		}
	}
	closedir(dir);
	return;
}
	
