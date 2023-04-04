#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno; // File descriptors and port number
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in server_address, client_address;
    int n;
    
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    /*
    Create a socket
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Family version (IPV4), type (TCP)
    if (sockfd < 0)
        error("ERROR opening socket");

    /*
     - Get the port number
     - Setup the host_addr structure for use in bind call
     - Automatically be filled with current host's IP address
     - Convert short integer value for port must be converted into network byte order
    */
    bzero((char *)&server_address, sizeof(server_address));

    portno = atoi(argv[1]); // Get the port number from the command line

    server_address.sin_family = AF_INET; // Ipv4
    server_address.sin_addr.s_addr = INADDR_ANY; // Set the server address to `locahost`
    server_address.sin_port = htons(portno); // !important

    /*
     Bind socket to port
     bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     bind() passes file descriptor, the address structure, and the length of the address structure
     This bind() call will bind  the socket to the current IP address on port, portno
    */
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) // ! important
        error("ERROR on binding");

     /*
     Listen to the incoming connections.
     Place all incoming connection into a backlog queue until accept() accepts the connection.
     Set the maximum size for the backlog queue to 5.
    */
    listen(sockfd, 5);

    /*
     Accept() returns a new socket file descriptor for the accepted connection.
    */
    clilen = sizeof(client_address);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_address, &clilen);
    
    if (newsockfd < 0)
        error("ERROR on accept");

    printf("Server received a connection!\n");
    
    /*
     Send a string to the new socket
    */
    send(newsockfd, "Hello from the server!\n", 22, 0);

    bzero(buffer, 256);

    n = read(newsockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("Message from client: %s\n", buffer);

    close(newsockfd);
    close(sockfd);
    return 0;
}
