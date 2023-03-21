/*
Example of race condition with two threads.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int order; // :(

void* place_order(void* arg)
{
	unsigned long i = 0;
	order += 1;

	printf("\n Order #%d received\n", order);

	// Delay for a few couple
	for (i = 0; i < (0xFFFFFFFF); i++) 
		;
	printf("\n Order #%d is ready\n", order);

	return NULL;
}

int main(void)
{
	int i = 0;
	int error;

	// Create a thread for the two clients
	while (i < 2) {
		// Call the place_order function for each thread
		error = pthread_create(&(tid[i]), NULL, &place_order, NULL);
		if (error != 0)
			printf("\nThread can't be created : [%s]", strerror(error));
		i++;
	}

	// Wait for both threads to complete execution
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
