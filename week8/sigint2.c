/*
Example: Signal handler for CTRL-C using sigaction
*/

#include "apue.h"

void sighandler(int signum)
{
    printf("\nSignal caught!\n");
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = sighandler;
    sigemptyset(&(sa.sa_mask));
    sigaddset(&(sa.sa_mask), SIGINT);
    sigaction(SIGINT, &sa, NULL);

    for (int i = 0; i < 5; i++)
    {
        printf("Sleeping...\n");
        sleep(5);
        printf("Awake\n");
    }
}