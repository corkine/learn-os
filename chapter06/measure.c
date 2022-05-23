#define _GNU_SOURCE //for CPU_ZERO, CPU_SET
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //for open
#include <sched.h> //for sched_setaffinity
#include <unistd.h> //for read, write, close
#include <sys/time.h> //for gettimeofday and timeval

float diffTime(struct timeval *start, struct timeval *end) {
  return (float)(end->tv_sec * 1e9 + end->tv_usec -
                 start->tv_sec * 1e9 - start->tv_usec);
}

int main(int argc, char **argv) {
  // measure syscall
  int fd = open("temp.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU),
      nloops = 100000;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  for (size_t i = 0; i < nloops; i++)
    read(fd, NULL, 0);
  gettimeofday(&end, NULL);
  printf("system call %f us\n\n", diffTime(&start, &end) / nloops);
  close(fd);

  // measure context switch
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(0, &set);

  int pp1[2], pp2[2];
  printf("pipe1 return %d\n", pipe(pp1));
  printf("pipe2 return %d\n", pipe(pp2));
  pid_t t = fork();
  if (t == -1) {
    perror("fork error");
  } else if (t == 0) {
    printf("sched cpu %d\n",
           sched_setaffinity(getpid(), sizeof(cpu_set_t), &set));
    for (size_t i = 0; i < nloops; i++) {
      read(pp1[0], NULL, 0);
      write(pp2[1], NULL, 0);
    }
  } else {
    printf("sched cpu %d\n",
           sched_setaffinity(getpid(), sizeof(cpu_set_t), &set));
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < nloops; i++) {
      write(pp1[1], NULL, 0);
      read(pp2[0], NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("context switch %f us\n", diffTime(&start, &end) / nloops);
  }

  return 0;
}