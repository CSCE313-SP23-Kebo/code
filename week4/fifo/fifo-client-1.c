/*
Example: A client process that sends six messages to the server
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char const *argv[]) {

const char *FIFO = "/tmp/MY_FIFO";

/* Use the file name to open the FIFO for writing */
int fifo = open (FIFO, O_WRONLY);
assert (fifo != -1);

/* Open the FIFO 6 times, writing an int each time */
for (int index = 5; index >= 0; index--)
  {
    /* Write 5, 4, 3, 2, 1, 0 into the FIFO */
    int msg = index;
    write (fifo, &msg, sizeof (int));

    /* Add a slight delay each time */
    sleep (1);
  }

/* Close the FIFO */
close (fifo);

  return 0;
}
