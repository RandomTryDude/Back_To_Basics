#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 4444


int main(void){
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = {0};
	char detransformed[1024] = {0};
	char ascii[1024] = {0};
	char filename[9];
	
	int fd = socket(AF_INET , SOCK_STREAM , 0);
	
    	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
   	address.sin_port = htons(PORT);
	
	bind(fd, (struct sockaddr*)&address, sizeof(address));
	
	listen(fd,0);
	
	int fd_client = accept(fd , (struct sockaddr*)&address , &addrlen);
	
	read(fd_client , filename , sizeof(filename)-1);
	
	printf("\nRecieved filename: %s\n",filename);
	
	int size = read(fd_client , buffer , sizeof(buffer)-1); // binary
	//printf("%s,%i\n",buffer,size);
	
	
	int binary = 0;
	int counter = 0;
	
	for(int i=0 ; i < size ; i ++) {
		int num = buffer[i] - '0';
		if(binary == 0){
			for(int l = 0 ; l < num ; l ++) {
			detransformed[counter++] = '0' ;
			}}
			
		else{
			for(int l = 0 ; l < num ; l ++) {
			detransformed[counter++] = '1' ;
			}}
		binary = !binary;
	
	}
	int index = 0;
	int length = strlen(detransformed);
	
	for (int i = 0; i < length; i += 8) {
        	char byte[9] = {0};  // Temporary buffer to hold 8 bits + null terminator
       		strncpy(byte, &detransformed[i], 8);  // Copy 8 bits
       		byte[8] = '\0';    

   
        	int ascii_value = strtol(byte, NULL, 2);
        	ascii[index++] = (char)ascii_value;  
    	}

    	ascii[index] = '\0';  // Null-terminate the ASCII string
    	printf("Content: \n%s\n", ascii);
    	//printf("%s",ascii);
	
	
	//printf("%s",detransformed);
	return 0;
}
	
