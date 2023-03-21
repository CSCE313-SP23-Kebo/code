#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#define FIFO_NAME "TUNNEL"
int main(void)
{
  char s[300];
  int num, fd;
  mkfifo(FIFO_NAME, 0666); // create FIFO

  printf("Waiting for reader...\n");
  fd = open(FIFO_NAME, O_WRONLY); // open
  if (fd < 0)
    return 0;

  printf("Reader ready.\nEnter some text.\n");
  while (fgets(s, sizeof s, stdin))
  {
    if (!strcmp(s, "quit"))
      break;
    if ((num = write(fd, s, strlen(s))) == -1)
      perror("write");
    else
      printf("Sender :wrote %d bytes\n", num);
  }
  // unlink (FIFO_NAME);
  return 0;
}
