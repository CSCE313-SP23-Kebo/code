/**
 *A C program to demonstrate working of fork(), process table entries, and zombies.
 **/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void func(int signum)
{
    wait(NULL);
}
 
int main()
{
    int i;
    int pid = fork();
    if (pid == 0)
        for (i=0; i<20; i++)
            printf("I am Child\n");
    else
    {
        signal(SIGCHLD, func);
        printf("I am Parent\n");
        while(1);
    }
}