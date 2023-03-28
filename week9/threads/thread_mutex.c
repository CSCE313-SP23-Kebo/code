/*
Example of two threads running with MUTEX synchronization.
Note: To compile a C program with pthread.h in LINUX using GCC or G++, use the –lpthread option after the compile command.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int order;
pthread_mutex_t key; // MUTEX

void *place_order(void *arg)
{
	// Acquire a mutex lock
	pthread_mutex_lock(&key); 

	unsigned long i = 0;
	order += 1;
	printf("\n Order #%d received\n", order);

	// Delay: making coffee order ...
	for (i = 0; i < (0xFFFFFFFF); i++)
		;

	printf("\n Order #%d is ready\n", order);

	// Release the mutex lock
	pthread_mutex_unlock(&key);

	return NULL;
}

int main(void)
{
	int i = 0;
	int error;

	if (pthread_mutex_init(&key, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return 1;
	}

	while (i < 2)
	{
		error = pthread_create(&(tid[i]), NULL, &place_order, NULL);
		if (error != 0)
			printf("\nThread can't be created :[%s]",
				   strerror(error));
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_mutex_destroy(&key);

	return 0;
}
