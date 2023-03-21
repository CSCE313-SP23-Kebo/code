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
  printf("Waiting for writer...\n");
  fd = open(FIFO_NAME, O_RDONLY);
  printf("got a writer\n");
  do{
    if ((num = read(fd, s, 300)) == -1)
      perror("read");
    else {
      s[num] = '\0';
      printf("Received: Read %d bytes: \"%s\"\n", num, s);
    }
  } while (num > 0);
  return 0;
}
