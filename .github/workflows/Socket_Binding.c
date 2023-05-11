#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        return 1;
    }

    // clear the server address structure
    memset((char*) &serv_addr, 0, sizeof(serv_addr));

    // set up the server address structure
    portno = 12345;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        return 1;
    }

    // listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // accept a client connection
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        return 1;
    }

    // receive data from the client
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        return 1;
    }
    printf("Here is the message: %s\n", buffer);

    // send a response to the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0) {
        perror("Error writing to socket");
        return 1;
    }

    // close the sockets
    close(newsockfd);
    close(sockfd);

    return 0;
}
