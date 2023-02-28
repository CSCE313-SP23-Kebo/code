/**
 * C program to illustrate write system Call
 **/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sz;

    int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 00644);
    if (fd < 0)
    {
        perror("r1");
        exit(1);
    }

    sz = write(fd, "hello aggies\n", strlen("hello aggies\n"));

    printf("called write(%d, \"hello aggies\\n\", %d). It returned %d.\n", fd, strlen("hello aggies\n"), sz);

    close(fd);
}
