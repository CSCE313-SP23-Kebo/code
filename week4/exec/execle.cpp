/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    const char *file = "/usr/bin/bash";
    const char *arg1 = "-c";
    const char *arg2 = "echo $ENV1 $ENV2!";
    const char *const env[] = {"ENV1=Hello", "ENV2=World", NULL};
    execle(file, file, arg1, arg2, NULL, env);
    return 0;
}
