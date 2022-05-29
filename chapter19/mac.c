#pragma GCC push_options
#pragma GCC optimize("O0")
// or use gcc -O0
#include <fcntl.h>
#include <mach/thread_act.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/// 计算 gettimeofday 耗时和精度
void checkTime() {
  struct timeval start, end;
  long all = 0;
  long temp = 0;
  for (size_t i = 0; i < 1000; i++) {
    gettimeofday(&start, NULL);
    temp = i * 1;
    gettimeofday(&end, NULL);
    all = (end.tv_sec - start.tv_sec) * 1e6 + end.tv_usec - start.tv_usec;
  }
  printf("check for loop %d, avg delta us is %.10f\n", 1000, all / 1000.0);
}

/// intel *86 pageSize is 4KB
void tlb(long pageSize, long numPages) {
  int jump = pageSize / sizeof(int);
  int a[numPages];
  for (size_t i = 0; i < numPages; i += jump)
    a[i] += 1;
}

void setAffinity() {
  thread_affinity_policy_data_t data = {1};
  thread_policy_set(getpid(), THREAD_AFFINITY_POLICY, (thread_policy_t)&data,
                    1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Need input Number of pages\n");
    exit(-1);
  }
  setAffinity();
  // checkTime();
  int nLoops = 1e9;
  int numPages = atoi(argv[1]);
  int pageSize = 4000; // on intel x86-64
  struct timeval start, end;
  printf("num pages is: %d, ", numPages);
  long allTime = 0;
  int a[numPages];
  for (size_t i = 0; i < numPages; i++)
    a[i] = 0; //init to hotwarm
  int jump = pageSize / sizeof(int);
  for (size_t i = 0; i < nLoops; i++) {
    gettimeofday(&start, NULL);
    // very bad: will init array each time
    // tlb(4000, numPages);
    for (size_t i = 0; i < numPages; i += jump)
      a[i] += 1;
    gettimeofday(&end, NULL);
    allTime +=
        (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
  }
  printf("cost time: %.5f us\n", allTime * 1.0 / nLoops);
}

#pragma GCC pop_options