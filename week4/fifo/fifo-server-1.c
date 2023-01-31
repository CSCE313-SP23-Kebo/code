/*
Example: The basic structure of a server process using a FIFO
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char const *argv[]) {

  /* Create the FIFO*/
  const char *FIFO = "/tmp/MY_FIFO"; // Define the name of the FIFO special file
  assert (mkfifo (FIFO, S_IRUSR | S_IWUSR) == 0);

  /* Open the FIFO. Delete FIFO if open() fails */
  int fifo = open (FIFO, O_RDONLY);
  if (fifo == -1)
  {
    fprintf (stderr, "Failed to open FIFO\n");
    unlink (FIFO);
    return 1;
  }

  /* Main server loop */
  while (1)
  {
    int req = 0;
    if (read (fifo, &req, sizeof (int)) != sizeof (int))
    continue;

    /* If we read a 0, quit; otherwise print hello */
    if (req == 0)
    break;
    printf ("hello\n");
  }

  /* Read a 0 from the FIFO, so close and delete the FIFO */
  close (fifo);
  printf ("Deleting FIFO\n");
  unlink (FIFO);

  return 0;
}
