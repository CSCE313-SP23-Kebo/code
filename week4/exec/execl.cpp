/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    const char *file = "/usr/bin/echo";
    const char *arg1 = "Hello world!";
    execl(file, file, arg1, NULL);
    return 0;
}
