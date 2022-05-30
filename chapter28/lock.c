#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct lock_t {
  int flag;
} lock_t;

int TestAndSet(int *old, int new) {
  int oldValue = *old;
  *old = new;
  return oldValue;
}

int CompareAndSwap(int *ptr, int expected, int new) {
  int actual = *ptr;
  if (actual == expected)
    *ptr = new;
  return actual;
}

int CompareAndSwapReal(int *ptr, int old, int new) {
  unsigned char ret;
  __asm__ __volatile__("   lock\n"
                       "   cmpxchgl %2,%1\n"
                       "   sete %0\n"
                       : "=q"(ret), "=m"(*ptr)
                       : "r"(new), "m"(*ptr), "a"(old)
                       : "memory");
  return ret;
}

int LoadLinked(int *ptr) { return *ptr; }

int StoreConditional(int *ptr, int value) {
  if (/*No one update *ptr since LoadLinked to this addr*/ 1) {
    *ptr = value;
    return 1;
  } else
    return 0;
}

/* int FetchAndAdd(int *p) {
    return (*p)++;
}

typedef struct lock_f {
    int ticket; 
    int turn;
} lock_f;

void lock_f_init(lock_f *lock) {
    lock->ticket = 0;
    lock->turn = 0;
}

void lock(lock_f *lock) {
    int myTurn = FetchAndAdd(&lock->ticket);
    while (lock->turn != myTurn);
}

void unLock(lock_f *lock) {
    FetchAndAdd(&lock->turn);
} */

void init(lock_t *mutex) { mutex->flag = 0; }

void doLock(lock_t *mutex) {
  // while (TestAndSet(&mutex->flag, 1) == 1);
  // while (CompareAndSwap(&mutex->flag, 0, 1) == 1);
  //flag must be zero and no one visited LoadLinked then get lock
  //flag is not zero or someone visited LoadLinked then spin
  while (LoadLinked(&mutex->flag) || !StoreConditional(&mutex->flag, 1))
    ;
  mutex->flag = 1;
}

void doUnlock(lock_t *mutex) { mutex->flag = 0; }

int main(int argc, char **argv) {}