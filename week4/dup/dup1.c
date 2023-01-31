/*
Example: Creating a bash-like linkage between two processes
Parent is acting like 'bash' interpreting the command line: $ ls | sort
*/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int pipefd[2];
    char buffer[10];
    pid_t child_pid;
    memset(buffer, 0, sizeof(buffer)); /* Clear the buffer */

    /* Open the pipe */
    if (pipe(pipefd) < 0)
    {
        printf("ERROR: Failed to open pipe\n");
        exit(1);
    }

    /* 'sort' child process */
    assert((child_pid = fork()) >= 0);
    if (child_pid == 0)
    {
        /* 'sort' closes unused write end of the pipe */
        close(pipefd[1]);
        /* ...and uses the read end as standard input */
        dup2(pipefd[0], STDIN_FILENO);
        /* Reading from "stdin" now reads from the pipe */
        ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            exit(0);
        /* Trim off the trailing newline character */
        char *token = strtok(buffer, "\n");
        printf("'sort' process received '%s'\n", token);
        exit(0);
    }

    /* 'ls' child process */
    assert((child_pid = fork()) >= 0);
    if (child_pid == 0)
    {
        /* 'ls' closes the read end of the pipe */
        close(pipefd[0]);
        /* ...and uses the write end as standard output */
        dup2(pipefd[1], STDOUT_FILENO);

        /* printf() now writes to the pipe instead of the screen */
        printf("list of files\n");
        exit(0);
    }
    /* 'bash' parent closes both ends of the pipe within itself */
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
}
