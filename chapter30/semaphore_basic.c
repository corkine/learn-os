#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semLock, semCond;
volatile int count;

void *add1000(void *args) {
    sem_wait(&semLock);
    printf("adding in thread %s\n", args);
    for (int i = 0; i < 1000; ++i) count++;
    sem_post(&semLock);
    sem_post(&semCond);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t p1, p2;
    //信号量初始化接收参数和初始信号量（signed int）
    sem_init(&semLock, 0, 1);
    sem_init(&semCond, 0, 0);
    count = 0;
    pthread_create(&p1, NULL, add1000, "A");
    pthread_create(&p2, NULL, add1000, "B");
    sem_wait(&semCond);
    sem_wait(&semCond);
    printf("count is %d\n", count);
}