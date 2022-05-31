#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////// 单锁全局计数器 vs. 多锁多级级计数器 //////////////////////

typedef struct counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  c->lock = PTHREAD_MUTEX_INITIALIZER;
}

void inc(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value--;
  pthread_mutex_unlock(&c->lock);
}

void desc(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value++;
  pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  int value =  c->value;
  pthread_mutex_unlock(&c->lock);
  return value;
}

int main(int argc, char **argv) { printf("Hello\n"); }

#define NUMCPUS 8

typedef struct counter_s_t {
  int global;
  pthread_mutex_t glock;
  int local[NUMCPUS];
  pthread_mutex_t llock[NUMCPUS];
  int threshold;
} counter_s_t;

void initCounter(counter_s_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  c->glock = PTHREAD_MUTEX_INITIALIZER;
  for (size_t i = 0; i < NUMCPUS; i++) {
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

void update(counter_s_t *c, int threadId, int amt) {
  pthread_mutex_lock(&c->llock[threadId]);
  c->local[threadId] += amt;
  if (c->local[threadId] >= c->threshold) {
    pthread_mutex_lock(&c->glock);
    c->global += c->local[threadId];
    pthread_mutex_unlock(&c->glock);
    c->local[threadId] = 0;
  }
  pthread_mutex_unlock(&c->llock[threadId]);
}

/// 不精确但是快速的结果
int getFast(counter_s_t *c) {
  pthread_mutex_lock(&c->glock);
  int ans = c->global;
  pthread_mutex_unlock(&c->glock);
  return ans;
}

/// 获得请求此函数时刻的所有数据，加全局锁是为了避免有线程试图在
/// for 遍历的过程中将本地数据写入到全局导致不一致
int getAll(counter_s_t *c) {
  pthread_mutex_lock(&c->glock);
  int collect = 0;
  for (size_t i = 0; i < NUMCPUS; i++) {
      pthread_mutex_lock(&c->llock[i]);
      collect += c->local[i];
      pthread_mutex_unlock(&c->llock[i]);
  }
  int all = collect + c->global;
  pthread_mutex_unlock(&c->glock);
  return all;
}

////////////////////// 带全局锁的链表 //////////////////////

typedef struct node_t {
    int key;
    struct node_t *next;
} node_t;

typedef struct list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void initList(list_t *l) {
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

int insertList(list_t *l, int key) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        pthread_mutex_unlock(&l->lock);
        return -1;
    }
    new->key = key;
    pthread_mutex_lock(&l->lock);
    new->next = l->head;
    l->head = new;
    pthread_mutex_unlock(&l->lock);
    return 0;
}

int searchList(list_t *l, int key) {
    pthread_mutex_lock(&l->lock);
    node_t *now = l->head;
    while (now) {
        if (now->key == key) {
            pthread_mutex_unlock(&l->lock);
            return 0;
        }
        now = now->next;
    }
    pthread_mutex_unlock(&l->lock);
    return -1;
}

////////////////////// 带头尾锁的队列 //////////////////////
typedef struct node_q {
    int value;
    struct node_q *next;
} node_q;

typedef struct queue_t {
    node_q *head;
    node_q *tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
} queue_t;

/// 初始化 queue，写入一个占位符
void initQueue(queue_t *q) {
    node_q *temp = malloc(sizeof(node_q));
    temp->next = NULL;
    q->head = q->tail = temp;
    q->headLock = PTHREAD_MUTEX_INITIALIZER;
    q->tailLock = PTHREAD_MUTEX_INITIALIZER;
}

/// 插入尾部，因为必定存在占位符 node，因此直接插入并更新尾部即可
void enqueue(queue_t *q, int value) {
    node_q *t = malloc(sizeof(node_q));
    t->value = value;
    t->next = NULL;
    pthread_mutex_lock(&q->tailLock);
    q->tail->next = t;
    q->tail = t;
    pthread_mutex_unlock(&q->tailLock);
}

/// 首个 node 仅仅是占位符，实际从第二个开始，找到则读值并更新头部
int dequeue(queue_t *q, int *res) {
    pthread_mutex_lock(&q->headLock);
    node_q *t = q->head;
    node_q *n = t->next;
    if (n == NULL) {
        pthread_mutex_unlock(&q->headLock);
        return -1;
    }
    *res = n->value;
    q->head = n;
    pthread_mutex_unlock(&q->headLock);
    free(t);
    return 0;
}

/////////////////////// 每个桶一个锁的并发散列表 //////////////////
#define BUCKETS (101)
typedef struct hash_t {
    list_t lists[BUCKETS];
} hash_t;

void initHash(hash_t *h) {
    for (int i = 0; i < BUCKETS; i++)
        initList(&h->lists[i]);
}

int insertHash(hash_t *h, int key) {
    return insertList(&h->lists[key % BUCKETS], key);
}

int lookupHash(hash_t *h, int key) {
    return searchList(&h->lists[key % BUCKETS], key);
}