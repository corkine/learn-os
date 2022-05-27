1.
[corkine@mazhangjing01 chapter15]$ ./relocation.py  -s 1

ARG seed 1
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x0000363c (decimal 13884)
  Limit  : 290

Virtual Address Trace
  VA  0: 0x0000030e (decimal:  782) --> segmentation fault
  VA  1: 0x00000105 (decimal:  261) --> 14145 0x3741
  VA  2: 0x000001fb (decimal:  507) --> segmentation fault
  VA  3: 0x000001cc (decimal:  460) --> segmentation fault
  VA  4: 0x0000029b (decimal:  667) --> segmentation fault

2.
如果需要所有虚拟地址都不超过界限，那么界限寄存器要等于最大虚拟地址的值，和基线、物理地址无关
./relocation.py -s 0 -n 10 -a x -l x
3.4.
如果界限为 100，那么 base 最大是 y - 100 才可以放到物理内存中
./relocation.py -s 0 -n 10 -l 100 -a x -p y
5.
在 0 到最大地址空间大小的随机数地址中，界限以内的是有效的，以外的是无效的，当且仅当偏移 + 界限小于等于物理内存最大长度的时候。
