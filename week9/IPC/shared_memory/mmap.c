#include "../../apue.h"
#include <sys/mman.h>
#include <sys/shm.h>
#include <fcntl.h>

int main()
{
    int fd = open("mario.txt", O_RDWR);
    off_t len = lseek(fd, 0, SEEK_END); // go to end to get file size
    lseek(fd, 0, SEEK_SET);             // seek back to the beginning
    char *buf = (char *)mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Copying bytes 20-29 off the file to the data buffer
    char data[11];
    memcpy(data, buf + 20, 10);
    data[10] = 0; // putting a NULL so it can be printed w/o crashing
    printf("Bytes 20-29 in file: %s\n", data);
    
    // writing to file
    memcpy (buf, "Hola Mundo", strlen ("Hola Mundo"));
    
    // unmapping
    munmap(buf, len);
    close(fd);
}
