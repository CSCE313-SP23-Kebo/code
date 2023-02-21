/*
This program opens a file and then unlinks it. The program then goes to sleep for 15 seconds before terminating.
*/
#include "apue.h"
#include <fcntl.h>

int main(void)
{
  if (open("tempfile", O_RDWR) < 0)
    printf("open error\n");
  if (unlink("tempfile") < 0)
    printf("unlink error\n");
  printf("file unlinked\n");
  sleep(15);
  printf("done\n");
  exit(0);
}