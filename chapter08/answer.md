1.
./mlfq.py -n 2 -j 2 -M 0 -s 1
2 个队列，2 个工作，关闭 I/O，分片 10, seed 1
q1 a-10 b-10
q2           a-4  b-66

turn-a: 24
trun-b: 76 + 14 = 90

resp-a: 0
resp-b: 10

turn: 57
resp: 5

2.
fig8.2
./mlfq.py -n 3 -q 10 -l 0,200,0
fig8.3
./mlfq.py -n 3 -q 10 -l 0,200,0:100,20,0 
fig8.4
./mlfq.py -n 3 -q 10 -l 0,200,10 -i 1
fig8.5
./mlfq.py -n 3 -q 10 -l 0,200,0:110,200,5:115,200,5 -i 10 --stay --boost 50
fig8.6
./mlfq.py -n 3 -q 10 -l 0,200,0:0,200,9 -i 10 --stay
./mlfq.py -n 3 -q 10 -l 0,200,0:0,200,9 -i 10
fig8.7
./mlfq.py -n 3 -Q 10,20,30 -l 0,200,0:0,200,0 -i 10

3.
只用将 n 设置为 1 即可实现轮转
./mlfq.py -n 1 -q 10 -l 0,200,0:0,200,0

4.
./mlfq.py -n 2 -q 100 -l 0,200,0:0,200,99 -i 1 --stay
./mlfq.py -n 2 -q 100 -l 0,300,0:0,300,99 -i 1 --stay

5.
10 个程序在运行：-B 20
20 个程序在运行：-B 10
./mlfq.py -n 2 -Q 10,20 -B 10
40 个程序在运行：-B 5

6.
一般添加到末尾给其它程序执行空间
./mlfq.py -n 3 -q 10 -l 0,200,10:0,200,10 -i 1 -c
但使用 -I 可将其移动到头部，但需要满足最大连续执行时间限制。

0 2 10
1 2 10 
1 1 10
0 1 10
0 0 90
1 0 90
0 0 90
1 0 90