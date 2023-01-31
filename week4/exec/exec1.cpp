/*
Example: Execvp
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

int main()
{
    char *args[] = {"ls", "-l", "-a", NULL};
    cout << "=====BEFORE========" << endl;
    execvp(args[0], args);
    cout << "======AFTER========" << endl;
}

