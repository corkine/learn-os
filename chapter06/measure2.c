#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1e9

int main(int argc, char *argv[]) {
  int pipefd_1[2];

  struct timespec start, stop;
  clockid_t clk_id = CLOCK_REALTIME;

  // for child and parent process run on the same cpu
  cpu_set_t set;
  int parentCPU, childCPU;

  char testChar = 'a'; /* Use for test */

  if (argc != 5) {
    fprintf(stderr, "Usage: %s parent-cpu child-cpu times\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  parentCPU = atoi(argv[1]);
  childCPU = atoi(argv[2]);
  int const times = atoi(argv[3]);
  int const writeEh = atoi(argv[0]);

  CPU_ZERO(&set);

  if (pipe(pipefd_1) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  char ch;
  switch (fork()) {
  case -1: /* error */
    perror("fork");
    exit(EXIT_FAILURE);

  case 0: /* child process */
    CPU_SET(childCPU, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
      perror("set cpu for child process");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < times; ++i) {
      if (!writeEh)
        write(pipefd_1[1], &ch, 1);
      else
        read(pipefd_1[0], &ch, 1);
    }

    exit(EXIT_SUCCESS);

  default: /* parent process */
    CPU_SET(parentCPU, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
      perror("set cpu for parent process");
      exit(EXIT_FAILURE);
    }

    if (0 > clock_gettime(clk_id, &start))
      return perror("clock_gettime"), 1;
    for (int i = 0; i < times; ++i) {
      if (writeEh)
        write(pipefd_1[1], &ch, 1);
      else
        read(pipefd_1[0], &ch, 1);
    }
    if (0 > clock_gettime(clk_id, &stop))
      return perror("clock_gettime"), 1;

    printf("the average cost of io is: %lf nsec\n",
           ((stop.tv_sec - start.tv_sec) * BILLION + stop.tv_nsec -
            start.tv_nsec) /
               times);
  }

  exit(EXIT_SUCCESS);
}
