1.
> ffs.py -f in.largefile -L 4
/ 挂载在 g0 #i0 g0@d0 上
/a 挂载在 g0 #i1 g1@d1-4 g1-9@d0-3 上
group inodes     data
    0 /a-------- /aaaa----- ---------- ---------- 
    1 ---------- aaaa------ ---------- ---------- 
    2 ---------- aaaa------ ---------- ---------- 
    3 ---------- aaaa------ ---------- ---------- 
    4 ---------- aaaa------ ---------- ---------- 
    5 ---------- aaaa------ ---------- ---------- 
    6 ---------- aaaa------ ---------- ---------- 
    7 ---------- aaaa------ ---------- ---------- 
    8 ---------- aaaa------ ---------- ---------- 
    9 ---------- aaaa------ ---------- ---------- 

symbol  inode#  filename     filetype  
/            0  /            directory 
a            1  /a             regular 

2.
> ffs.py -f in.largefile -L 30 -M -S -c
group inodes     data
    0 /a???????? /a{29}
    1 ?????????? aaaaaaaaaaa???????????????????

3.
filespan 为访问同一文件或同目录其它数据所需要的最远内存距离
扩散为 4 的 filespan（文件 372，目录 373） 要远高于扩散为 100 的 filespan
（文件 59，目录 60） ，其顺序性更差，随机性更强。
> ffs.py -f in.largefile -L 4 -T -c
> ffs.py -f in.largefile -L 100 -T -c

4.
当存在大量的小文件时，L4 平均文件 filespan 15 目录 filespan 27
L30 与之没有任何区别。因为文件过小无法触发大文件随机分配的动作。
> ffs.py -f in.manyfiles -L 4 -T -c

5.
FFS 在降低 dirspan 上表现比 VSFS 好得多，小文件的目录亲近性很好
但仅限于单层目录（而不是日常更容易的 2-3 层目录）
> ffs.py -f in.manyfiles -L 4 -T -c

6.
I5 的目录亲近性为 81，I10 的目录亲近性为 27，I15 的目录亲近性为 32
可见每个组的 inode 表数量是一个需要根据负载决策的问题，当数量极端的少
其丧失了目录的亲近性，当数量极端的大，也损害了目录的亲近性（不过略微好一点）。
> ffs.py -f in.manyfiles -i 10 -T -c
> ffs.py -f in.manyfiles -i 10 -T -c

7.
使用 -A 2 策略，dirspan 为 48，当使用默认策略，dirspan 为 81
> ffs.py -f in.manyfiles -i 5 -A 2 -c -T
> ffs.py -f in.manyfiles -i 5 -c -T
dirspan for -A2 is 27, dirspan for default is 27
> ffs.py -f in.manyfiles -i 10 -A 2 -c -T
> ffs.py -f in.manyfiles -i 10 -c -T
dirspan for -A2 is 32, dirspan for default is 32
> ffs.py -f in.manyfiles -i 15 -A 2 -c -T
> ffs.py -f in.manyfiles -i 15 -c -T
可以看到对于 inode 占比很小的时候，使用更好的策略可提升亲近性，
当 inode 占比很大时，这种策略也不更坏
但其代价是维护和检查所有目录中的内容并选取最好的一个，比
直接排序寻找最大的空 inode 更复杂

8.
i b d f h 被剩余，其中 i 填充到了之前的空位上，其非常的不连续
读写效率比较差（其实还好，因为一次性的将一个 group 数据获取出来，
不过还是没有完全顺序读的效果好），但放在大环境下，日常操作会导致大量
的外部碎片，其需要通过缓冲写入和定期碎片整理来避免这种性能的降低（写入慢，读取慢）。
> ffs.py -f in.fragmented -v -c
    0 /ib-d-f-h- /ibidifihi iii------- ---------- 
9
这个策略要好一些，以写入时稍微复杂的查找换来了读取的效率
当然，它增大了 filespan 和 dirspan，降低了亲近性。
> ffs.py -f in.fragmented -v -C 2 -c
    0 /ib-d-f-h- /-b-d-f-hi iiiiiii--- ---------- 