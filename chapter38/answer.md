1.
> ./raid.py  -n 5 -R 20 -L 0 -s 1
LOGICAL READ from addr:2 size:4096
  disk 2 offset 0
LOGICAL READ from addr:15 size:4096
  disk 3 offset 3
LOGICAL READ from addr:9 size:4096
  disk 1 offset 2
LOGICAL READ from addr:13 size:4096
  disk 1 offset 3
LOGICAL READ from addr:1 size:4096
  disk 1 offset 0
> ./raid.py  -n 5 -R 20 -L 1 -s 1
LOGICAL READ from addr:2 size:4096
  disk 1 offset 1
LOGICAL READ from addr:15 size:4096
  disk 3 offset 7
LOGICAL READ from addr:9 size:4096
  disk 2 offset 4
LOGICAL READ from addr:13 size:4096
  disk 2 offset 6
LOGICAL READ from addr:1 size:4096
  disk 2 offset 0
> ./raid.py  -n 5 -R 20 -L 4 -s 1 (LS)
LOGICAL READ from addr:2 size:4096
  disk 2 offset 0
LOGICAL READ from addr:15 size:4096
  disk 0 offset 5
LOGICAL READ from addr:9 size:4096
  disk 0 offset 3
LOGICAL READ from addr:13 size:4096
  disk 1 offset 4
LOGICAL READ from addr:1 size:4096
  disk 1 offset 0
> ./raid.py  -n 5 -R 20 -L 5 -s 1
LOGICAL READ from addr:2 size:4096
  level0, use disk 0,1,2, disk 2 offset 0
LOGICAL READ from addr:15 size:4096
  level5, use disk 3,0,1  disk 3 offset 5
LOGICAL READ from addr:9 size:4096
  level3, use disk 1,2,3  disk 1 offset 3
LOGICAL READ from addr:13 size:4096
  level4, use disk 0,1,2  disk 1 offset 4
LOGICAL READ from addr:1 size:4096
  level0, use disk 0,1,2  disk 1 offset 0

> ./raid.py  -n 5 -R 20 -L 5 -s 1 -5 LA
LOGICAL READ from addr:2 size:4096
  read  [disk 2, offset 0]   
LOGICAL READ from addr:15 size:4096
  read  [disk 0, offset 5] level5 0,1,4 -> disk 0 offset 5
LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 3]   
LOGICAL READ from addr:13 size:4096
  read  [disk 1, offset 4]   
LOGICAL READ from addr:1 size:4096
  read  [disk 1, offset 0]   

LS 和 LA 的区别在于，统计不同层数的磁盘，哪个磁盘作为第一个，LS 让校验盘固定，
其它磁盘从校验盘开始数，而 LA 则使用原来的顺序，让校验盘移动。

2.
大块的计算简单的将除数改为盘数 * 块大小即可。

3.
略。

4.
当请求的大小增加时，即顺序负载情况下，底层 I/O 会有较少的寻道和旋转耗时，实际 I/O 速度
更接近传输速度。RAID-4 和 RAID-5 的大块和小块读速度都不错，相比较 RAID 1，在大块读
上优势更加明显。

5.
结果符合预期，对于小块随机读的效率 RAID 0 和 RAID 1、RAID 5 最高，RAID 4 次之。

6.
随着磁盘数量增加，读写的吞吐量都增加了。

7.
使用随机写的话，RAID 0 的效率最高，其次是 RAID 1，其可以利用一半的 NR，再其次是
RAID 5，其可以利用 1/4 的 NR，最差的是 RAID 4，其只有 R/2。
随着磁盘数量的增加，RAID 0,1,5 吞吐量都增加了，而 RAID 4 则保持不变（受限于单个校验盘）。

8.
大块顺序读的效率都挺好，其中 RAID 0 最高，RAID 1 最差（镜像），RAID 4-5 次之
大块顺序写的效率和读的效率表现类似。