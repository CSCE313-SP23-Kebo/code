/*
Example of signal sets and sigprocmask
Note: When the program is exucating, type Control-backslash, in the terminal to send a quit signal.

Example:
$ ./a.out
ˆ\                      generate signal once (before 5 seconds are up)
SIGQUIT pending         after return from sleep
caught SIGQUIT          in signal handler
SIGQUIT unblocked       after return from sigprocmask
ˆ\Quit(coredump)        generate signal again

$ ./a.out
ˆ\ˆ\ˆ\ˆ\ˆ\ˆ\ˆ\ˆ\ˆ\ˆ\    generate signal 10 times (before 5 seconds are up)
SIGQUIT pending
caught SIGQUIT          signal is generated only once
SIGQUIT unblocked
ˆ\Quit(coredump)        generate signal again
*/

#include "apue.h"

static void sig_quit(int);

int main(void)
{
    // Signal sets
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        printf("can’t catch SIGQUIT");

    // Initialize the signal set to empty, with all signals excluded from the set.
    sigemptyset(&newmask);

    // Add SIGQUIT to the set of signal to ignore
    sigaddset(&newmask, SIGQUIT);

    // The process blocks the signals in the set newmask (SIGQUIT), saving its current signal mask in oldset (to restore later)
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf("SIG_BLOCK error");

    /*
    Sleep for 5 seconds.
    Any occurrence of the quit signal (SIGQUIT) during this period is blocked and won’t be delivered until the signal is unblocked.
    At the end of the 5-second sleep, we check whether the signal is pending and unblock the signal.
    */
    sleep(5);

    // Return the set of signals that are pending for delivery
    if (sigpending(&pendmask) < 0)
        printf("sigpending error");

    if (sigismember(&pendmask, SIGQUIT))
        printf("\nSIGQUIT pending\n");
    /*
     Restore the signal mask which unblocks SIGQUIT.
     Note that we saved the old mask when we blocked the signal.
     To unblock the signal, we do a SIG_SETMASK of the old mask.
     Note: Alternatively, we could SIG_UNBLOCK only the signal that we had blocked. i.e. - > sigprocmask(SIG_UNBLOCK, &newmask, NULL);
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK error");

    printf("SIGQUIT unblocked\n");
    sleep(5); /* SIGQUIT here will terminate with core file */
    exit(0);
}

// Handler for SIG_QUIT
static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        printf("can’t reset SIGQUIT");
}