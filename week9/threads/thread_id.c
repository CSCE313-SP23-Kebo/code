/*
Example: this program prints thread IDs
Note: To compile a C program with pthread.h in LINUX using GCC or G++, use the –lpthread option after the compile command.
*/

#include "../apue.h"
#include <pthread.h>
pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    // Return the ID of the thread
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
           (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
    printids("new thread: ");
    return ((void *)0);
}

int main(void)
{
    int err;
    // Create a thread and return the ID of the newly created thread.
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
        printf("can’t create thread");
    printids("main thread:");
    sleep(1);
    exit(0);
}
