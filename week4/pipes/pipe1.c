/*
Example: pipe()
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[]){
	int fd[2];
	char buf[30];
	//create UNMANED pipe
	if(pipe(fd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	//write to pipe
	printf("writing to file descriptor #%d\n", fd[1]);
	write(fd[1],"CSCE 313",9);

	//read from pipe
	printf("reading from file descriptor #%d\n", fd[0]);
	read(fd[0], buf,9);
	printf("read \"%s\"\n",buf);
	return 0;
}
