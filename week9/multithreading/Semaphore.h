#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

class Semaphore{
private:
    int value;
    pthread_mutex_t m;
    pthread_cond_t c;
public:
    Semaphore (int _v){
        value = _v;
        pthread_mutex_init(&m, 0);
        pthread_cond_init (&c, 0);
    }
    ~Semaphore (){
        pthread_mutex_destroy (&m);
        pthread_cond_destroy (&c);
    }
    void P(){
        pthread_mutex_lock (&m);
        while (value <= 0)
            pthread_cond_wait (&c, &m);
        value --;
        pthread_mutex_unlock (&m);
    }
    void V(){
        pthread_mutex_lock (&m);
        value ++;
        pthread_cond_signal (&c);
        pthread_mutex_unlock (&m);
    }
};