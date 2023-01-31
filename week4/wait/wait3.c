#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int pid = fork(); // New process
  switch(pid)
  {
     case -1:
           printf("\n There is a failure in creating a child process");
           exit(1);
     case 0:
           printf("\n This is a child Process\n");
           break;
     default:
           printf("\n This is a parent Process\n");
           break;
   }

/* This section of program waits for the child to finish */
   if (pid !=0) /* It is parent process */
   {
        int stat_val; // Status variable
        int child_pid = wait(&stat_val);
        if (child_pid == -1)
        {
           printf("\n There is no child process \n");
           exit(1);
        }
        
        if (WIFEXITED(stat_val))
            printf("\n Child exited normally with return status %d\n", WEXITSTATUS(stat_val));
        else
            printf("\n Child terminated Abnormally");
    }
  }  