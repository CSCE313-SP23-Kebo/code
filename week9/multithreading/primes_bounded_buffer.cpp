#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <mutex>
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include "BoundedBuffer.h"

#define NUM_OF_CORES 8
#define MAX_PRIME 1000000
using namespace std;

mutex m;
int found_primes = 0;

struct timeval start_time, end_time;

void timediff(struct timeval &start, struct timeval &end)
{
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) / (int)1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec) % ((int)1e6);
    cout << "Took " << secs << "." << usecs << " seconds" << endl;
}

class workload
{
public:
    int start, end;
    workload(int s, int e)
    {
        start = s, end = e;
    }
    workload()
    {
        start = end = 0;
    }
};

void do_generate(int start, int end, BoundedBuffer *bb)
{
    int nworkloads = 10000;
    int divisor = (int)ceil((double)(end - start + 1) / nworkloads);
    for (int i = 0; i < nworkloads; i++)
    {
        workload w(start, min(start + divisor - 1, end));
        bb->push((char *)&w, sizeof(w));
        start += divisor;
    }
}

void do_primes(int threadid, BoundedBuffer *bb)
{
    int primes = 0;
    while (true)
    {
        workload w;
        bb->pop(&w, sizeof(w));

        if (w.start == 0 && w.end == 0)
            break;

        for (int num = w.start; num <= w.end; ++num)
        {
            int i;
            for (i = 2; (i <= num) && (num % i != 0); ++i)
                ;
            if (i == num)
                ++primes;
        }
    }
    struct timeval tend;
    gettimeofday(&tend, 0);
    cout << "Thread [" << threadid << "] "
         << "Calculated " << primes << " primes in the given ranges";
    timediff(start_time, tend);
    m.lock();
    found_primes += primes;
    m.unlock();
}

int main(int ac, char *av[])
{
    int maxprime = atoi(av[1]);

    int w = atoi(av[2]);
    thread workers[w];

    BoundedBuffer bb(50);

    gettimeofday(&start_time, 0);

    thread workloadgenerator(do_generate, 1, maxprime, &bb);
    for (int i = 0; i < w; i++)
    {
        workers[i] = thread(do_primes, i + 1, &bb);
    }
    workloadgenerator.join();

    // pushing quit messages
    workload wq(0, 0);
    for (int i = 0; i < w; i++)
    {
        bb.push(&wq, sizeof(wq));
    }

    for (int i = 0; i < w; i++)
    {
        workers[i].join();
    }

    gettimeofday(&end_time, 0);
    cout << "Found a total of " << found_primes << " prime numbers in range [1," << MAX_PRIME << "]" << endl;
    timediff(start_time, end_time);
}
