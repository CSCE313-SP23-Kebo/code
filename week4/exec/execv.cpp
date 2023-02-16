/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    char *file = "/usr/bin/echo";
    char *const args[] = {"/usr/bin/echo", "Hello world!", NULL};
    execv(file, args);
    return 0;
}
