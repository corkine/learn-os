#include <stdio.h>
#include <stdlib.h>
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void *args) {
    for (int i = 0; i < loops; i++) 
        counter++;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1,p2;
    printf("init value: %d\n", counter);
    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1,NULL);
    Pthread_join(p2,NULL);
    printf("final value: %d\n", counter);
    return 0;
}

