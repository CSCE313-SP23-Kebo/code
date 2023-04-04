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
    Get port number
    */
    portno = atoi(argv[2]);

    /*
    Create socket
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /*
    Get the server hostname
    */
    server = gethostbyname(argv[1]);
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
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(portno);

    /*Connect to server*/
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        error("ERROR connecting");

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