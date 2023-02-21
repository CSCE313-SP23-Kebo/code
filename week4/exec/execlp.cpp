/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    const char *file = "echo";
    const char *arg1 = "Hello world!";
    execlp(file, file, arg1, NULL);
    return 0;
}
