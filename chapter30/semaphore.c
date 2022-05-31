#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>

#define MAX 100
int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int temp = buffer[use];
    use = (use + 1) % MAX;
    return temp;
}

sem_t empty, full, mutex;

void *producer(void *args) {
    int loops = (int) args;
    for (int i = 0; i < loops; ++i) {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *args) {
    int i, tmp = 0;
    while (tmp != -1) {
        sem_wait(&full);
        sem_wait(&mutex);
        tmp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("%d\n", tmp);
    }
    return NULL;
}

int main(int argc, char **argv) {
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
}

typedef struct rwlock_t {
    sem_t lock;
    sem_t writeLock;
    int readers;
} rwlock_t;

void initRWLock(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writeLock, 0, 1);
}

void acquireReadLock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1)
        sem_wait(&rw->writeLock);
    sem_post(&rw->lock);
}

void releaseReadLock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0)
        sem_post(&rw->writeLock);
    sem_post(&rw->lock);
}

void acquireWriteLock(rwlock_t *rw) {
    sem_wait(&rw->writeLock);
}

void releaseWriteLock(rwlock_t *rw) {
    sem_post(&rw->writeLock);
}

sem_t forks[5];
pthread_t people[5];
int left(int p) { return p; }
int right(int p) { return (p + 1) % 5; }
void getForks(int p) {
    if (p == 4) {
        sem_wait(forks[right(p)]);
        sem_wait(forks[left(p)]);
    } else {
        sem_wait(forks[left(p)]);
        sem_wait(forks[right(p)]);
    }
}
void putForks(int p) {
    sem_post(forks[left(p)]);
    sem_post(forks[right(p)]);
}
void *runEach(void *args) {
    int p = (int) args;
    while (1) {
        getForks(p);
        //eat
        putForks(p);
    }
}
void run() {
    for (int i = 0; i < 5; ++i)
        sem_init(forks + i, 0, 1);
    for (int i = 0; i < 5; ++i)
        pthread_create(people + i, NULL, runEach, (void *) i);
    while (1);
}

typedef struct zem_t {
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} zem_t;

void zemInit(zem_t *z, int value) {
    z = malloc(sizeof(zem_t));
    z->value = value;
    pthread_mutex_init(&z->lock, NULL);
    pthread_cond_init(&z->cond, NULL);
}

void zemWait(zem_t *z) {
    pthread_mutex_lock(&z->lock);
    while (z->value <= 0)
        pthread_cond_wait(&z->cond, &z->lock);
    z->value--;
    pthread_mutex_unlock(&z->lock);
}

void zemPost(zem_t *z) {
    pthread_mutex_lock(&z->lock);
    z->value++;
    pthread_cond_signal(&z->cond);
    pthread_mutex_unlock(&z->lock);
}