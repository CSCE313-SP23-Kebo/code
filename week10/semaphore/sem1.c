#include <stdlib.h>     // abort()
#include <unistd.h>     // sleep()
#include <stdio.h>      // printf()
#include <pthread.h>    // pthread_create()

#include "semaphores.h" // s_init(), s_wait(), s_signal(), s_destroy()

#define N     5
#define SLEEP 1

semaphore_t *sem;

void *thread() {
  for (int i = 0; i < N; i++) {
    sleep(SLEEP);
    s_signal(sem);
  }
  pthread_exit(0);
}

int main(void) {
  pthread_t tid;
  sem = s_init(0);

  if (pthread_create(&tid, NULL, thread, NULL) != 0) {
    perror("pthread_create()");
    abort();
  }

 for (int i = 0; i < N; i++) {
   printf("  main(%d) waiting on a semaphore ...\n", i);
   s_wait(sem);
   printf("  main(%d)     semaphore signaled by thread.\n", i);
 }

 s_destroy(sem);

}