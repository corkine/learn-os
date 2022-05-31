#include <stdio.h>
#include <pthread.h>

volatile int done = 0;

void *handleSimple(void *args) {
    printf("child start\n");
    done = 1;
    return NULL;
}

int waitSimple(int argc, char **argv) {
    pthread_t c;
    printf("parent start\n");
    pthread_create(&c, NULL, handleSimple, NULL);
    //spin to wait child thread
    while (done == 0);
    printf("parent end\n");
    return 0;
}

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void *handleCond(void *args) {
    printf("child start\n");
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t p;
    printf("parent start\n");
    pthread_create(&p, NULL, handleCond, NULL);
    //use cond but not spin
    //不使用锁不行：如果父进程检查完 done = 0 后准备睡眠，子进程更新 done 父进程睡死
    pthread_mutex_lock(&m);
    //不使用 done 不行：如果子进程先结束，父进程后结束，那么父进程被卡死到 wait
    while (done == 0)
        pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
    printf("parent end\n");
    return 0;
}