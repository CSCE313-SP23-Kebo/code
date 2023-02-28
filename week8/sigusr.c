/*
This example shows a signal handler that catches either of the two user-defined signals and prints the signal number.
We invoke the program in the background and use the kill(1) command to send it signals.
The kill(1) command and the kill(2) function just send a signal to a process or process group. Whether that signal terminates the process depends on which signal is sent and whether the process has arranged to catch the signal.
*/
#include "apue.h"
static void sig_usr(int); /* one handler for both signals */

int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) // Dispostion for SIGUSR1
        printf("can’t catch SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) // Disposition for SIGUSR2
        printf("can’t catch SIGUSR2");
    for (;;)
        pause(); // The pause function suspends the calling process until a signal is received.
}

static void sig_usr(int signo) /* argument is signal number */
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}
