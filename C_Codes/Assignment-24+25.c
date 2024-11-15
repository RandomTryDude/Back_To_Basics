#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void){
	int fd;
	char buffer[] = "AABBCCDD";
	char file[] = "testfile.txt";
	
	fd = open(file,O_WRONLY | O_CREAT, S_IRWXU);
	if(fd == -1){
		printf("Couldnt open file");
	}
	else{
		printf("File opened with success");

	}
	write(fd,buffer,sizeof(buffer)-1);
	return 0;




}
