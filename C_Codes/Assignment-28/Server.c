#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4444

int main(void) {
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    int fd, fd_client;

    // Create socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(fd, 1) < 0) {
        perror("Listen failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Listening on port %d...\n", PORT);

    // Accept connection
    fd_client = accept(fd, (struct sockaddr*)&address, &addrlen);
    if (fd_client < 0) {
        perror("Accept failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Connection established from %s:%d\n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Interaction loop
    while (1) {
        printf("> ");
        fflush(stdout);

        // Read input from operator
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        // Send command to client
        if (send(fd_client, buffer, strlen(buffer), 0) < 0) {
            perror("Send failed");
            break;
        }

        // Read response from client
        memset(buffer, 0, sizeof(buffer));
        if (recv(fd_client, buffer, sizeof(buffer) - 1, 0) <= 0) {
            perror("Receive failed or client disconnected");
            break;
        }

        // Print client response
        printf("%s", buffer);
    }

    // Clean up
    close(fd_client);
    close(fd);
    return 0;
}
