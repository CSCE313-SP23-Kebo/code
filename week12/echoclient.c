/*
Example:
Usage example: $ ./a.out host port
*/

#include "apue.h"
#if defined(SOLARIS)
#include <netinet/in.h>
#endif
#include <netdb.h>
#include <arpa/inet.h>
#if defined(BSD)
#include <sys/socket.h>
#include <netinet/in.h>
#endif

int main(int argc, char **argv)
{
    int clientfd;
    size_t n;
    char *host, *port, buf[MAXLINE];

    host = argv[1];
    port = argv[2];

    if ((clientfd = open_clientfd(host, port)) == -1)
        exit(1);

    while (fgets(buf, sizeof buf - 1, stdin) != NULL)
    {
        write(clientfd, buf, strlen(buf));
        n = read(clientfd, buf, sizeof buf - 1);
        if (n >= 0)
        {
            buf[n] = '\0';
            fputs(buf, stdout);
        }
    }
    close(clientfd);
    exit(0);
}

int open_clientfd(char *hostname, char *port)
{
    int clientfd, error;
    struct addrinfo address, *hostaddresses = NULL;

    /* Find out the server's IP address and port */
    memset(&address, 0, sizeof address);
    address.ai_flags = AI_ADDRCONFIG | AI_V4MAPPED;
    address.ai_family = AF_INET6;
    address.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(hostname, port, &address, &hostaddresses) != 0)
        return -2;

    /* We take advantage of the fact that AF_* and PF_* are identical */
    clientfd = socket(hostaddresses->ai_family, hostaddresses->ai_socktype, hostaddresses->ai_protocol);
    if (clientfd == -1)
        return -1; /* check errno for cause of error */
    /* Establish a connection with the server */
    if (connect(clientfd, hostaddresses->ai_addr, hostaddresses->ai_addrlen) == -1)
        return -1;
    freeaddrinfo(hostaddresses);
    return clientfd;
}
