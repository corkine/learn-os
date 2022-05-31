#include <stdio.h>
#include <pthread.h>

#define MAX 100
int buffer[MAX];
int fill = 0;
int use = 0;
int count = 0;

void put(int v) {
    buffer[fill] = v;
    fill = (fill + 1) % MAX;
    count++;
}

int get() {
    int t = buffer[use];
    use = (use + 1) % MAX;
    count--;
    return t;
}

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int loops = (int) arg;
    for (int j = 0; j < loops; ++j) {
        pthread_mutex_lock(&lock);
        //生产槽满则等待消费者消费
        while (count == MAX) //因为信号释放的很随意，可能虚假唤醒，用 while
            pthread_cond_wait(&cond, &lock);
        put(j);
        //生产产品后通知可能等待的消费者（仅对于消费者等待情景有用）
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
}

void *consumer(void *arg) {
    int i;
    while (1) {
        pthread_mutex_lock(&lock);
        //没有产品消费则等待生产者生产
        while (count == 0) //因为信号释放的很随意，可能虚假唤醒，用 while
            pthread_cond_wait(&cond, &lock);
        int tmp = get();
        //消费者消费后通知生产者生产（仅对于生产槽满情景有用）
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        printf("%d\n", tmp);
    }
    //这里的唤醒可能导致 1. 同条件虚假唤醒，其使用 while 可以解决
    //2. 不同条件虚假唤醒，消费者通知生产和生产者通知消费使用同一条件导致混淆唤醒
}

pthread_cond_t emptyCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t fillCond = PTHREAD_COND_INITIALIZER;

void *producerRich(void *arg) {
    int loops = (int) arg;
    for (int j = 0; j < loops; ++j) {
        pthread_mutex_lock(&lock);
        while (count == MAX)
            pthread_cond_wait(&fillCond, &lock);
        put(j);
        pthread_cond_signal(&emptyCond);
        pthread_mutex_unlock(&lock);
    }
}

void *consumerRich(void *arg) {
    int i;
    while (1) {
        pthread_mutex_lock(&lock);
        while (count == 0)
            pthread_cond_wait(&emptyCond, &lock);
        int tmp = get();
        pthread_cond_signal(&fillCond);
        pthread_mutex_unlock(&lock);
        printf("%d\n", tmp);
    }
}

int main(int argc, char **argv) {

}