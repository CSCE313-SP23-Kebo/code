/**
 *A C program to demonstrate working of fork(), process table entries, and zombies.
 **/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int i;
    int pid = fork();

    if (pid == 0)
    {
        for (i = 0; i < 20; i++)
            printf("I am Child\n");
    }
    else
    {
        printf("I am Parent\n");
        while (1)
            ;
    }
}
