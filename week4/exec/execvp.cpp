/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    char *file = "echo";
    char *const args[] = {"/usr/bin/echo", "Hello world!", NULL};
    execvp(file, args);
    return 0;
}
