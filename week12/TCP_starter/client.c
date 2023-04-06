/*
Usage: .\client localhost <server port number>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in server_address;
    struct hostent *server;

    char buffer[256];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    /*
    Get and convert the port number from the second argument passed to the program
    */
    // TODO

    /*
    Create a new socket of type SOCK_STREAM using the Internet Protocol version 4 (IPv4) address family
    */
    // TODO
    if (sockfd < 0)
        error("ERROR opening socket");

    /*
    Get the server hostname from the first argument passed to the program using the gethostbyname() function
    */
    // TODO
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /*
    The variable server_address is a structure of type struct sockaddr_in. This structure has four fields.
    The first field is short sin_family, which contains a code for the address family.
    AF_INET is an address family that designate the type of addresses that the socket can communicate with (in this case, Internet Protocol v4 addresses).
    */
    bzero((char *)&server_address, sizeof(server_address));
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    // TODO: Add IPV4 address family to the server address struct
    // TODO: Add port number to the server address struct

    /*Establish a connect to the server*/
    // TODO

    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");

    printf("%s\n", buffer);
    close(sockfd);
    return 0;
}