/*
Example Using two pipes for bidirectional communication between parent and child
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main(int argc, char* argv[]){

  int p2cfd[2]; /* parent-to-child */
  int c2pfd[2]; /* child-to-parent */
  char buffer[10];
  ssize_t bytes_read = 0;

  /* Clear the buffer and open the pipe */
  memset (buffer, 0, sizeof (buffer));
  if ((pipe (p2cfd) < 0) || (pipe (c2pfd) < 0))
  {
    printf ("ERROR: Failed to open pipe\n");
    exit (1);
  }

  /* Create a child process */
  pid_t child_pid = fork ();
  assert (child_pid >= 0);

  if (child_pid == 0)
  {
    /* Child closes write end of p2c*/
    close (p2cfd[1]);
    /* Child closes read end of c2p */
    close (c2pfd[0]);
    bytes_read = read (p2cfd[0], buffer, 10);
    if (bytes_read <= 0)
    exit (0);
    printf ("Child received: '%s'\n", buffer);

    /* Child sends response of "goodbye" */
    strncpy (buffer, "goodbye", sizeof (buffer));
    write (c2pfd[1], buffer, 10);
    exit (0);
  }

  /* Parent closes read end of p2c */
  close (p2cfd[0]); // sys call 1
  /*Parent closes write end of c2p*/
  close (c2pfd[1]); // sys call 2

  /* Parent sends 'hello' and waits */
  strncpy (buffer, "hello", sizeof (buffer));
  printf ("Parent is sending '%s'\n", buffer);
  write (p2cfd[1], buffer, sizeof (buffer));

  /* Parent reads response back from child */
  bytes_read = read (c2pfd[0], buffer, 10);
  if (bytes_read <= 0)
  exit (1); /* should receive response */
  printf ("Parent received: '%s'\n", buffer);
}
