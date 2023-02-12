#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	char c1, c2, c3;
	int fd1 = open("sample.txt", O_RDONLY, 0);
	int fd2 = open("sample.txt", O_RDONLY, 0);
	int fd3 = open("sample.txt", O_RDONLY, 0);
	printf("%d %d %d\n", fd1, fd2, fd3);
	dup2(fd2, fd3);
	read(fd1, &c1, 1);
	printf("c = %c\n", c1);
	read(fd2, &c2, 1);
	printf("c = %c\n", c2);
	read(fd3, &c3, 1);
	printf("c = %c\n", c3);
	exit(0);
}
