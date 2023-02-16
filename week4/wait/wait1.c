#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

/* This program forks and the prints whether the process is
 *   - the child (the return value of fork() is 0), or
 *   - the parent (the return value of fork() is not zero)
 */

int main( void ) {
	char *argv[3] = {"Command-line", ".", NULL};
	int status_of_child;

	int pid = fork();

	if ( pid == 0 ) { // Child process
		execvp( "find", argv );
	}

	/* Put the parent to sleep for 2 seconds--let the child finished executing */
	wait(&status_of_child);

	printf( "Finished executing the parent process\n"
	        " - the child won't get here--you will only see this once\n" );

	return 0;
}