/*
Example: C program to implement pipe in Linux
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	// array of 2 size fd[0] is for reading
	// and fd[1] is for writing over a pipe
	int fd[2];  // File descriptor

	// opening of pipe using pipe(fd)
	char buff[10];
	if (pipe(fd) == -1)
	{
		perror("pipe"); // error in pipe
		exit(1); // exit from the program
	}

	// writing a string "code" in pipe
	write(fd[1], "code\n", 6);  // write(pipe end, string, number of bytes)
	printf("\n");

	// reading pipe now buff is equal to "code"
	read(fd[0], buff, 6);

	// it will print "code"
	printf("%s", buff);
}
