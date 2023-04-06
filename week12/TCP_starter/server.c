/*
Usage: .\server <port number>
Use a non-priveleged port number above 1024
*/

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
    int sockfd, newsockfd, portno;
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
    Create a new socket of type SOCK_STREAM using the Internet Protocol version 4 (IPv4) address family
    */
    // TODO
    if (sockfd < 0)
        error("ERROR opening socket");

    /*
     - Get the port number
     - Setup the host_addr structure for use in bind call
     - Automatically be filled with current host's IP address
     - Convert short integer value for port must be converted into network byte order
    */
    bzero((char *)&server_address, sizeof(server_address));

    portno = atoi(argv[1]);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // TODO: Add IPV4 address family to the server address struct
    // TODO: Add port number to the server address struct

    /*
     Bind socket to port
     bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     bind() passes file descriptor, the address structure, and the length of the address structure
     This bind() call will bind  the socket to the current IP address on port, portno
    */
    // TODO

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
    // TODO
    
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
