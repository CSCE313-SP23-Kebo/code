#include<unistd.h>

int main(void) {
  write(1, "Hello, world\n", 13); //System to the OS to access / Write to the display
  return 0;
}
