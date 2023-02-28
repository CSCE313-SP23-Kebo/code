/*
Example: Use sigaction() to establish a handler for the SIGINT signal.
*/

#include "apue.h"
#include <signal.h>

static void handler(int signum)
{
    printf("Another action.\n");
}

int main()
{
    struct sigaction sa;

    // Define the action the signal will take
    sa.sa_handler = handler;

    sigemptyset(&sa.sa_mask);

    // System calls interrupted by this signal are automatically restarted.
    sa.sa_flags = SA_RESTART;

    // Change the action of SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1)
        printf("sigaction failed!");

    for (;;)
        pause(); // The pause function suspends the calling process until a signal is received.
}
