/*
   This example produces the contents of a directory by opening it,
   rewinding it, and closing it.
 */
#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

int main()
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir("/")) == NULL)
        perror("opendir() error");
    else
    {
        puts("1- contents of root:");
        while ((entry = readdir(dir)) != NULL)
            printf("%s \n", entry->d_name);

        puts("");
        rewinddir(dir); // Rewind to the 'beginning' of the parent folder
    
        puts("\n2- Try to acces the directory content once again");
        while ((entry = readdir(dir)) != NULL)
            printf("%s \n", entry->d_name);
        closedir(dir);
        puts("");
    }
}