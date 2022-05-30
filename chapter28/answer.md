1. 
> ./x86.py -p flag.s
一个带有内存位锁的 for 循环递增某值的程序
flag == 0 获得锁
flag := 1
count++
flag := 0
index-- < 0 退出

2.
> ./x86.py -p flag.s -R ax,bx -M flag,count -c
使用上述默认值时，循环只执行了一次，第一个进程
首次获得所，其代码较短，执行完后才切换到下一个进程
此时下一个进程也获得锁，锁没有起到作用，但代码正常工作
，即每个进程都对 count 进行了正确操作 -> 2

3.
> ./x86.py -p flag.s -R ax,bx -M flag,count -a bx=2,bx=2
同样的锁没有用到，每个线程执行了两次循环，最终得到了 count -> 4

4.
> ./x86.py -p flag.s -R ax,bx -M flag,count -a bx=12,bx=12 -i 10
当循环的次数变多，中断的密度增加，得到错误的概率上升。

5.
查看代码可知，其采用了 xchg 实现了 TestAndSet，总是想给 mutex 设置为 1，如果
失败（返回 1，旧值）则表明存在锁，SPIN，反之（返回 0，旧值）则表明没有锁。

释放锁简单的通过将 mutex 设置为 0 即可。

6.
> ./x86.py -p test-and-set.s -R ax,bx -M mutex,count -a bx=12,bx=12 -i 10 -S
总是能得到正确的结果，但中断越少，执行的指令数越少，中断越多，执行的指令数越多
因为在每次循环中都获得锁和释放锁，如果在这个临界区内中断，被调度的进程将不得不 SPIN
以花费完毕此时间片产生浪费。

7.
如下所示，thread 0 获取锁后，thread 1 一直抢占 CPU 执行时间会被饿死（一直 SPIN）。
> ./x86.py -p test-and-set.s -R ax,bx -M mutex,count -a bx=1,bx=1 -c -P 00001111111111111111111111111111111111

mutex count      ax    bx          Thread 0                Thread 1         

    0     0       0     1   
    0     0       1     1   1000 mov  $1, %ax
    1     0       0     1   1001 xchg %ax, mutex
    1     0       0     1   1002 test $0, %ax
    1     0       0     1   1003 jne  .acquire
    1     0       0     1   ------ Interrupt ------  ------ Interrupt ------  
    1     0       1     1                            1000 mov  $1, %ax
    1     0       1     1                            1001 xchg %ax, mutex
    1     0       1     1                            1002 test $0, %ax
    1     0       1     1                            1003 jne  .acquire
    1     0       1     1                            1000 mov  $1, %ax
    1     0       1     1                            1001 xchg %ax, mutex
    1     0       1     1                            1002 test $0, %ax
    1     0       1     1                            1003 jne  .acquire
    1     0       1     1                            1000 mov  $1, %ax
    1     0       1     1                            1001 xchg %ax, mutex
    1     0       1     1                            1002 test $0, %ax

8.
peterson.s 中的代码在 peterson 算法基础上进行了 count++

9.
> ./x86.py -p peterson.s -M turn,flag,count -c -i 5
特殊的中断导致 count 不等于 2，i 越大，count 为 2 的概率越高

10.
比如下面的测试中，线程 0 执行到获取了 count 但还没有 ++ 的时候，被中断给线程 1，
导致最后的结果为 1 而非 2。很明显这里表明 peterson 算法没有生效，因为 线程 1
也进入了 count 处理逻辑。
> ./x86.py -p peterson.s -M turn,flag,count -R cx -c -i 4 -P 000000000011111111111
>  turn  flag count      cx          Thread 0                Thread 1         

    0     0     0       0   
    0     0     0       0   1000 lea flag, %fx
    0     0     0       0   1001 mov %bx, %cx
    0     0     0       0   1002 neg %cx
    0     0     0       1   1003 add $1, %cx
    0     1     0       1   1004 mov $1, 0(%fx,%bx,4)
    1     1     0       1   1005 mov %cx, turn
    1     1     0       1   1006 mov 0(%fx,%cx,4), %ax
    1     1     0       1   1007 test $1, %ax
    1     1     0       1   1008 jne .fini
    1     1     0       1   1012 mov count, %ax
    1     1     0       0   ------ Interrupt ------  ------ Interrupt ------  
    1     1     0       0                            1000 lea flag, %fx
    1     1     0       0                            1001 mov %bx, %cx
    1     1     0       0                            1002 neg %cx
    1     1     0       1                            1003 add $1, %cx
    1     1     0       1                            1004 mov $1, 0(%fx,%bx,4)
    1     1     0       1                            1005 mov %cx, turn
    1     1     0       1                            1006 mov 0(%fx,%cx,4), %ax
    1     1     0       1                            1007 test $1, %ax
    1     1     0       1                            1008 jne .fini
    1     1     0       1                            1012 mov count, %ax
    1     1     0       1                            1013 add $1, %ax
    1     1     0       1   ------ Interrupt ------  ------ Interrupt ------  
    1     1     0       1   1013 add $1, %ax
    1     1     1       1   1014 mov %ax, count
    1     0     1       1   1015 mov $0, 0(%fx,%bx,4)
    1     0     1       1   1016 mov %cx, turn
    1     0     1       1   1017 halt
    1     0     1       1   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1     0     1       1                            1014 mov %ax, count
    1     0     1       1                            1015 mov $0, 0(%fx,%bx,4)
    1     0     1       1                            1016 mov %cx, turn
    1     0     1       1                            1017 halt

11.
相符，获取锁的方式是通过 FetchAndAdd ticket 进行的，释放锁的方式是通过 FetchAndAdd turn 进行的。
如果不是自己的 turn，那么等待释放锁递增当前序号直到轮到自己。

12.
> ./x86.py -p ticket.s -a bx=1000,bx=1000
每个线程都是公平的

13.
> ./x86.py -p ticket.s -t 3 -a bx=13,bx=13,bx=13
虽然 tickets 保证了公平，但是和其他 SPIN 锁一样，
单核心 CPU 多线程调度当线程越多，而调度周期越长，那么自旋浪费的 CPU 也就越严重。

14.
在题目 7 的场景中，使用自旋有效的避免了等待
> ./x86.py -p yield.s -R ax,bx -M mutex,count -a bx=1,bx=1 -c -P 00001111111111111111111111111111111111

15.
其首先检查 mutex，如果有锁，则直接自旋，如果 mutex 没有被赋值，则执行 test-and-set
这种二阶段锁的方法提高了效率，减少了指令。