1.
./lottery.py -j 3 -s 1
job0 1 84 
job1 7 25(109) 
job2 4 44(153)
    651593 -> 119 -> job2 3
    788724 -> 9 -> job0 0
job1 7 25
job2 3 44(69)
    93859 -> 19 -> job1 6
    28347 -> 57 -> job2 2
    835765 -> 37 -> job2 1
    432767 -> 68 -> job2 0
job1 6 25
    762280 -> 5 -> job1 5
    2106 ->  -> job1 4
    445387 ->  -> job1 3
    721540 ->  -> job1 2
    228762 ->  -> job1 1
    945271 ->  -> job1 0
./lottery.py -j 3 -s 2
./lottery.py -j 3 -s 3

2.
./lottery.py -j 2 -l 10:1,10:100 -c
模拟显示，job1 执行完毕后才执行 job0，当彩票数量非常不均等
会导致调度同样的不均等。

3.
./lottery.py -j 2 -l 100:100,100:100 -c -s 1
4
10
4
1
19
7
15
9
8
3
不公平性：avg: 8

4.
./lottery.py -j 2 -l 100:100,100:100 -q 10 -c -s 1
40
10
10
10
40
20
60
50
60
20
不公平性：avg：32

