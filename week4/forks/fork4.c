/*
Example: The following program creates a new process by invoking system call fork()
It also uses system calls getpid() to get the calling process’s ID and getppid() for the parent’s ID
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    printf("Hello!! My ID is %d, my parent ID is %d.\n",getpid(), getppid());
    pid_t pid = fork();
    printf("Bye!! My ID is %d, my parent ID is %d.\n",getpid(), getppid());
    return 0;
}
