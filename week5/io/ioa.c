/*
 Example: C program to illustrate the open system call
*/ 
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
extern int errno;
int main()
{	
	int fd = open("foo.txt", O_RDONLY | O_CREAT | O_APPEND);
	
	printf("fd = %d\n", fd);
	
	if (fd ==-1)
	{
		// print which type of error have in a code
		printf("Error Number %d\n", errno);
		
		// print program detail "Success or failure"
		perror("Program");				
	}
	return 0;
}
