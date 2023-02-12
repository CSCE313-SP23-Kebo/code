#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    /* from apue.h */
    printf("%% "); /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; /* replace newline with null */
        if ((pid = fork()) < 0)
        {
            printf("fork error");
        }
        else if (pid == 0)
        { /* child */
            execlp(buf, buf, (char *)0);
            printf("couldn’t execute: %s", buf);
            exit(127);
        }
        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error");
        printf("%% ");
    }
    exit(0);
}