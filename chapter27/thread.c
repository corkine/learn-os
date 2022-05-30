#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *callFunc(void *args) {
  printf("running on thread: %s\n", args);
  //注意不能将一个栈分配的数据作为指针传递出去
  char *errorHERE = "World";
  char *rightHERE = malloc(5);
  rightHERE = "World";
  return (void *)rightHERE;
}

// with -pthread or -lpthread
int threadDemo1(int argc, char **argv) {
  pthread_t t1, t2, t3;
  //创建线程接收线程结构，配置栈大小和调度优先级的属性，栈
  //初始化函数和其参数，配置和参数都可以为 NULL
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&t1, &attr, callFunc, (void *)"Hello");
  char *answer = malloc(100);
  //等待线程结束，可以从中获取返回的数据，可以为 NULL
  pthread_join(t1, (void *)&answer);
  printf("answer is %s\n", answer);
}

int lockDemo(int argc, char **argv) {
    //pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t lock;
    //可以自动或手动初始化锁，这里可传入一些锁的参数
    pthread_mutex_init(&lock, NULL);
    //可 lock、unlock、trylock、timedlock
    pthread_mutex_lock(&lock);
    //pthread_mutex_trylock(&lock);
    //Cirtical Section START

    //Cirtical Section END
    pthread_mutex_unlock(&lock);
    //锁用完后必须销毁, 创建和销毁都可能成功或失败
    pthread_mutex_destroy(&lock);
}

int signalDemo1(int argc, char **argv) {
    //one thread:
    int ready = 0;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_lock(&lock);
    //必须是 while 循环，因为可能虚假唤醒
    while (ready == 0)
        //等待信号，进入休眠，同时释放锁
        pthread_cond_wait(&cond, &lock);
    //Do something HERE
    pthread_mutex_unlock(&lock);

    //another thread:
    pthread_mutex_lock(&lock);
    ready = 1;
    //发送信号，将上面进程唤醒
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv) {
    lockDemo(argc, argv);
}