1.
> ./x86.py -p loop.s -t 1 -i 100 -R dx

   dx          Thread 0         
    0   
    -1  1000 sub  $1,%dx
    -1  1001 test $0,%dx
    -1  1002 jgte .top
    -1  1003 halt

2.
没有竞态条件，因为 100 指令才会中断
> ./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx

   dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    0   1001 test $0,%dx
    0   1002 jgte .top
    -1  1000 sub  $1,%dx
    -1  1001 test $0,%dx
    -1  1002 jgte .top
    -1  1003 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    1                            1000 sub  $1,%dx
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
    0                            1002 jgte .top
    -1                           1000 sub  $1,%dx
    -1                           1001 test $0,%dx
    -1                           1002 jgte .top
    -1                           1003 halt

3.
中断频率让此程序实际执行过程行为不可预测，但是这种交替没有产生竞态条件
因为其没有共享变量，甚至没有发生内存访问
> ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx
> ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -c -s 5
   dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    3   ------ Interrupt ------  ------ Interrupt ------  
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    2   ------ Interrupt ------  ------ Interrupt ------  
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    2   ------ Interrupt ------  ------ Interrupt ------  
    1                            1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------  
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------  
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------  
    0   1001 test $0,%dx
    0   1002 jgte .top
    -1  1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------  
    0                            1000 sub  $1,%dx
    -1  ------ Interrupt ------  ------ Interrupt ------  
    -1  1001 test $0,%dx
    -1  1002 jgte .top
    -1  ------ Interrupt ------  ------ Interrupt ------  
    0                            1001 test $0,%dx
    0                            1002 jgte .top
    -1  ------ Interrupt ------  ------ Interrupt ------  
    -1  1003 halt
    0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    -1                           1000 sub  $1,%dx
    -1                           1001 test $0,%dx
    -1  ------ Interrupt ------  ------ Interrupt ------  
    -1                           1002 jgte .top
    -1                           1003 halt

4.
> ./x86.py -p looping-race-nolock.s -t 1 -M 2000
 2000          Thread 0         
    0   
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   1004 test $0, %bx
    1   1005 jgt .top
    1   1006 halt

5.
循环 3 次的原因是，bx = 3，因此循环了 3 遍
> ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000
2000          Thread 0                Thread 1         
    0   
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   1004 test $0, %bx
    1   1005 jgt .top
    1   1000 mov 2000, %ax
    1   1001 add $1, %ax
    2   1002 mov %ax, 2000
    2   1003 sub  $1, %bx
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   1000 mov 2000, %ax
    2   1001 add $1, %ax
    3   1002 mov %ax, 2000
    3   1003 sub  $1, %bx
    3   1004 test $0, %bx
    3   1005 jgt .top
    3   1006 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    3                            1000 mov 2000, %ax
    3                            1001 add $1, %ax
    4                            1002 mov %ax, 2000
    4                            1003 sub  $1, %bx
    4                            1004 test $0, %bx
    4                            1005 jgt .top
    4                            1000 mov 2000, %ax
    4                            1001 add $1, %ax
    5                            1002 mov %ax, 2000
    5                            1003 sub  $1, %bx
    5                            1004 test $0, %bx
    5                            1005 jgt .top
    5                            1000 mov 2000, %ax
    5                            1001 add $1, %ax
    6                            1002 mov %ax, 2000
    6                            1003 sub  $1, %bx
    6                            1004 test $0, %bx
    6                            1005 jgt .top
    6                            1006 halt

6.
2000 处的值为 2 或者 1, 每个线程的 for 只运行一次，且在运行的时候如果不会
在临界区 1000-1002 打断，则结果是 2（如 s 0 和 s 2），反之则是 1（如 s 1）
> ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0
 2000          Thread 0                Thread 1         
    ?   
    ?   1000 mov 2000, %ax
    ?   1001 add $1, %ax
    ?   1002 mov %ax, 2000
    ?   1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    ?                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1004 test $0, %bx
    ?   1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1006 halt
    ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?                            1006 halt
> ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1
 2000          Thread 0                Thread 1         
    ?   
    ?   1000 mov 2000, %ax
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    ?                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1001 add $1, %ax
    ?   1002 mov %ax, 2000
    ?   1003 sub  $1, %bx
    ?   1004 test $0, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1005 jgt .top
    ?   1006 halt
    ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1006 halt
> ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 2
 2000          Thread 0                Thread 1         
    ?   
    ?   1000 mov 2000, %ax
    ?   1001 add $1, %ax
    ?   1002 mov %ax, 2000
    ?   1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    ?                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1004 test $0, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?                            1004 test $0, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------  
    ?   1005 jgt .top
    ?   1006 halt
    ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?                            1005 jgt .top
    ?                            1006 halt


7.
一行和两行中断一次势必影响结果的正确性，三行及以上可能影响结果正确性
换言之，只要让 1000-1003 的临界区非原子的都会导致错误的答案
> ./x86.py -p looping-race-nolock.s -t 2 -a bx=1 -M 2000 -i 1


8.
同上
> ./x86.py -p looping-race-nolock.s -t 2 -a bx=100 -M 2000 -i 1

9.
> ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000
thread 0 是 singler，其发送完信号（写入到地址 2000）后退出，thread 1
从 2000 接收到信号，退出
 2000      ax          Thread 0                Thread 1         
    0       1   
    0       1   1000 test $1, %ax
    0       1   1001 je .signaller
    1       1   1006 mov  $1, 2000
    1       1   1007 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1       0                            1000 test $1, %ax
    1       0                            1001 je .signaller
    1       0                            1002 mov  2000, %cx
    1       0                            1003 test $1, %cx
    1       0                            1004 jne .waiter
    1       0                            1005 halt

10.
线程 0 是 waiter，1 是 singler，线程 0 一直在等待线程 1 的结果
> ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000
 2000      ax          Thread 0                Thread 1         
    ?       ?   
    ?       ?   1000 test $1, %ax
    ?       ?   1001 je .signaller
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   ------ Interrupt ------  ------ Interrupt ------  
    ?       ?                            1000 test $1, %ax
    ?       ?                            1001 je .signaller
    ?       ?                            1006 mov  $1, 2000
    ?       ?                            1007 halt
    ?       ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1005 halt

> ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 -i 1000
线程 0 等待 1000 次指令后轮到线程 1 执行完毕后才结束

> ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 -i 5
线程 0 很快就让渡出去给线程 1，线程 1 执行完后，交给线程 0 返回。
这意味着对于带有睡眠/唤醒的线程行为，合适的中断能够提升程序效率
 2000      ax          Thread 0                Thread 1         
    ?       ?   
    ?       ?   1000 test $1, %ax
    ?       ?   1001 je .signaller
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   ------ Interrupt ------  ------ Interrupt ------  
    ?       ?                            1000 test $1, %ax
    ?       ?                            1001 je .signaller
    ?       ?                            1006 mov  $1, 2000
    ?       ?                            1007 halt
    ?       ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?       ?   1002 mov  2000, %cx
    ?       ?   ------ Interrupt ------  ------ Interrupt ------  
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1005 halt