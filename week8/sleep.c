/*
Example: Using alarm and pause, we can put a process to sleep for a specified amount of time.
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void sig_alrm(int signo)
{
    printf("Alarm signal received. \n");
}
unsigned int sleep1(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return (seconds);

    alarm(seconds);    /* start the timer */
    pause();           /* next caught signal wakes us up */
    return (alarm(0)); /* turn off timer, return unslept time */
}

int main()
{
    printf("Before sleep.\n");
    sleep1(5);
    printf("After sleep.\n");
}