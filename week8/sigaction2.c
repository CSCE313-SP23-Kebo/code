/*
Example: Use the sigaction() function to establish signal catching functions.
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void check_mask(int sig, char *signame)
{

    sigset_t sigset;

    sigprocmask(SIG_SETMASK, NULL, &sigset);
    if (sigismember(&sigset, sig))
        printf("the %s signal is blocked\n", signame);
    else
        printf("the %s signal is unblocked\n", signame);
}

void catcher(int sig)
{
    printf("inside catcher() function\n");
    check_mask(SIGUSR1, "SIGUSR1");
    check_mask(SIGUSR2, "SIGUSR2");
}

int main(int argc, char *argv[])
{

    struct sigaction sigact, old_sigact;
    sigset_t sigset;

    /*
     * CONFIGURATION #1
     * Set up a signal handler by setting the signal mask to the empty signal set and
     * using the do-not-defer signal, and reset the signal handler to the SIG_DFL signal flag options.
     */
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_flags = sigact.sa_flags | SA_NODEFER | SA_RESETHAND;
    sigact.sa_handler = catcher;
    sigaction(SIGUSR1, &sigact, NULL);

    /*
     * Send a signal to this program by using kill(getpid(), SIGUSR1); (equivalent to raise(SIGUSR1))
     */
    printf("Raising a SIGUSR1 signal\n");
    kill(getpid(), SIGUSR1);

    /*
     * Get the current value of the signal handling action for SIGUSR1.  The signal-catching function should have been reset to SIG_DFL
     */
    sigaction(SIGUSR1, NULL, &old_sigact);
    if (old_sigact.sa_handler != SIG_DFL)
        printf("signal handler was not reset\n");

    /*
     * CONFIGURATION #2
     * Reset the signal-handling action for SIGUSR1
     */
    sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask, SIGUSR2);
    sigact.sa_flags = 0;
    sigact.sa_handler = catcher;
    sigaction(SIGUSR1, &sigact, NULL);

    /*
     * Send a signal to this program by using kill(getpid(), SIGUSR1)
     */
    printf("raise SIGUSR1 signal\n");
    kill(getpid(), SIGUSR1);

    /*
     * Get the current value of the signal-handling action for SIGUSR1.  catcher() should still be the signal catching function.
     */
    sigaction(SIGUSR1, NULL, &old_sigact);
    if (old_sigact.sa_handler != catcher)
        printf("signal handler was reset\n");

    return (0);
}