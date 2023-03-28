#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
void func(int *p, int x, mutex *m)
{
    // increment *p x times
    for (int i = 0; i < x; i++)
    {
        m->lock();

        *p = *p + 1;

        m->unlock();
    }
}
int main(int ac, char **av)
{
    int data = 0;
    int times = atoi(av[1]);
    mutex m;

    thread t1(func, &data, times, &m);
    thread t2(func, &data, times, &m);
    t1.join(); // pauses until first finishes
    t2.join(); // pauses until second finishes
    cout << "data = " << data << endl;
}
