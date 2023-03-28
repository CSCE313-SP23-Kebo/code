/*
Example: pthread_join() — Wait for a thread to end
Note: To compile a C program with pthread.h in LINUX using GCC or G++, use the –lpthread option after the compile command.
*/

#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *thread_fct(void *arg)
{
    char *ret;
    printf("thread() entered with argument '%s'\n", arg);
    if ((ret = (char *)malloc(20)) == NULL)
    {
        printf("malloc() error");
        exit(2);
    }
    strcpy(ret, "This is a test");
    pthread_exit(ret);
}

int main()
{
    pthread_t thid;
    void *ret;

    if (pthread_create(&thid, NULL, thread_fct, "thread 1") != 0)
    {
        printf("pthread_create() error");
        exit(1);
    }

    if (pthread_join(thid, &ret) != 0)
    {
        printf("pthread_join() error");
        exit(3);
    }

    printf("thread exited with %s\n", ret);
}