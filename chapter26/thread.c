#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static volatile int counter = 0;

void *thread_call(void *args) {
  printf("pid: %d, thread: %s\n", (int)getpid(), (char *)args);
  for (size_t i = 0; i < 100000; i++) {
    counter++;
  }
}

//gcc -lpthread -O0 -g thread.c;
//objdump -d main.out
int main() {
  pthread_t p1, p2;
  int rc = 0;
  rc = pthread_create(&p1, NULL, thread_call, "A");
  rc = pthread_create(&p2, NULL, thread_call, "B");
  rc = pthread_join(p1, NULL);
  rc = pthread_join(p2, NULL);
  printf("counter is %d\n", counter);
  return 0;
}