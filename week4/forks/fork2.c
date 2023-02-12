/*
Example: C program to differentiate a parent process from a child process after a fork
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

void forkexample()
{
	int child_status;
	// child process because return value zero
	if (fork() == 0)
	{
		printf("1. Hello from Child!\n");
		printf("1. My process ID is %d\n", getpid());
		printf("1. My parent process ID is %d\n", getppid());
	}

	// parent process because return value non-zero.
	else
	{
		wait(&child_status); // Waits at least one child process to return an exit status
		printf("2. Hello from Parent!\n");
		printf("2. My process ID is %d\n", getpid());
		printf("2. My parent process ID is %d\n", getppid());
	}
}
int main()
{
	forkexample();
	return 0;
}
