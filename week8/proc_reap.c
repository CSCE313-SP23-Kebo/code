/*
Example: Reaping child processes
This program receives signals from children processes and ends them one at a time.
*/

#include "apue.h"
#include <sys/types.h>
#include <sys/wait.h>

// Handler for the SIGCHLD signal
void do_something (int sig){
    printf("SIGCHLD received: change in status of child.\n");
    wait (0); // Waiting on any child process that returns
}

int main (){
    // signal handler: capture a change in the status of the child process and do something.
    signal (SIGCHLD, do_something); // *CHILD or *PARENT 
    
    // Create five child processes 
    // The i-th process sleeps for i seconds and then dies
    for (int i=1; i <= 5; i++){

        // Fork a new child process
        int pid = fork ();

        // If in the child process
        if (pid == 0){
            sleep (i); // Sleep for i seconds
            printf("Child %d is exiting\n", i);
            return 0; // Exit the child process i
        }
    }

    // The parent process stays in an infinite loop
    // busy doing something else
    while (1){
        printf("Parent is working\n");
        sleep (1);
    }
}