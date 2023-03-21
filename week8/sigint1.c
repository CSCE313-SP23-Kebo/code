/*
Example: Signal handler for CTRL-C using the signal() function
*/

#include "apue.h"

// Handler  to perform an operation if CTRL-C*/
void sighandler(int signum)
{
    printf("\nSignal caught!\n");
}

int main()
{
    // Option 1: Handle the signal
    // Define what to do when a signal is received - sighandler is the disposition when CTRL-C is received.
    //signal(SIGINT, sighandler);

    // Option 2: ignore the signal
    // signal(SIGINT, SIG_DFL);

    // Option 3: Use the default behavior
    signal(SIGINT, SIG_IGN);

    for (int i = 0; i < 5; i++)
    {
        printf("Sleeping...\n");
        sleep(5);
        printf("Awake\n");
    }
}