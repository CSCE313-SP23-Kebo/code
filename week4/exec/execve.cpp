/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    char *file = "/usr/bin/bash";
    char *const args[] = {"/usr/bin/bash", "-c", "echo Hello $ENV!", NULL};
    char *const env[] = {"ENV=World", NULL};
    execve(file, args, env);
    return 0;

}
