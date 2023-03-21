/*
Example: pipe()
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fds[2];
	pipe(fds); // connect the pipe

	// Fork a new child process
	int pid = fork();

	// If in the child process
	if (pid == 0)
	{
		sleep(3);
		char *message = "May the Force be with you";
		printf("Child process: Sent %s\n", message);
		write(fds[1], message, strlen(message) + 1);
	}
	else
	{
		char buf[100];
		read(fds[0], buf, 100);
		printf("Parent process: Received %s\n", buf);
	}
	return 0;
}
