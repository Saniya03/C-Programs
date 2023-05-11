#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, clientfd, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    const int size = 1024;
    char buffer[size];

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    // set socket options
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("failed to set socket options");
        exit(EXIT_FAILURE);
    }

    // bind to port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    port = 8080;
    server_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("failed to bind to port");
        exit(EXIT_FAILURE);
    }

    // listen for clients
    if (listen(sockfd, 5) < 0) {
        perror("failed to listen for clients");
        exit(EXIT_FAILURE);
    }
    printf("Listening for clients on port %d...\n", port);

    // accept connections from clients
    while ((clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len)) > 0) {
        printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // receive data from client
        int n = recv(clientfd, buffer, size, 0);
        if (n < 0) {
            perror("failed to receive data from client");
            exit(EXIT_FAILURE);
        }

        // send response to client
        const char *response = "Hello from server";
        n = send(clientfd, response, strlen(response), 0);
        if (n < 0) {
            perror("failed to send response to client");
            exit(EXIT_FAILURE);
        }
      

        // close client socket
        close(clientfd);
    }

    // clean up
    close(sockfd);
    return 0;
}
