1.
> lfs.py -n 3 -s 0
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ] live [.,0] [..,0] -- -- -- -- -- -- 
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

create file /ku3
write to file /ku3 z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0
create file /qg9

FINAL file system contents:
[   0 ]  dead   checkpoint: 14 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]  dead   [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]  dead   type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]  dead   chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ]  dead   [.,0] [..,0] [ku3,1] -- -- -- -- -- 
[   5 ]  dead   type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]  dead   type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]  dead   chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ]  live   z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0
[   9 ]  live   type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8 
[  10 ]  dead   chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  11 ]  live   [.,0] [..,0] [ku3,1] [qg9,2] -- -- -- -- 
[  12 ]  live   type:dir size:1 refs:2 ptrs: 11 -- -- -- -- -- -- -- 
[  13 ]  live   type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  14 ]  live   chunk(imap): 12 9 13 -- -- -- -- -- -- -- -- -- -- -- -- -- 


2.
> lfs.py -n 3 -s 0 -c -o -i

3.
> lfs.py -o -F -s 100 -c -i
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ] live [.,0] [..,0] -- -- -- -- -- -- 
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

create file /us7 
[   0 ] live checkpoint: 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [us7,1] -- -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- 
[   7 ] live chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --

write file  /us7 offset=4 size=0
[   0 ] live checkpoint: 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live type:reg size:4 refs:1 ptrs: -- -- -- -- xx -- -- 
[   9 ] live chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --

write file  /us7 offset=7 size=7
[   0 ] live checkpoint: 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   10] live xxxxxxxxxxxxxxxxxxxx
[   11] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 10
[   9 ] live chunk(imap): 5 11 -- -- -- -- -- -- -- -- -- -- -- -- -- --

4.
> lfs.py -n 20 -s 1 -c -v -o
create file /tg4 
write file  /tg4 offset=6 size=0 
create file /lt0 
write file  /lt0 offset=1 size=7 
link file   /tg4 /oy3 
create file /af4 
write file  /tg4 offset=1 size=1 
write file  /lt0 offset=0 size=6 
write file  /oy3 offset=1 size=7 
delete file /tg4 
write file  /af4 offset=5 size=7 
write file  /af4 offset=5 size=2 
write file  /af4 offset=6 size=4 
write file  /lt0 offset=1 size=6 
write file  /lt0 offset=4 size=5 
create dir  /ln7 
write file  /oy3 offset=3 size=0 
create file /ln7/zp3 
create file /ln7/zu5 
delete file /oy3

live 的 inode 集中在最后面，分散在中间的是各个各个未动的数据，以及最前面的 CR
垃圾回收大多处理的是数据块。


5.
> lfs.py -L c,/foo:w,/foo,0,1:w,/foo,1,1:w,/foo,2,1:w,/foo,3,1 -o -c -v
这种情况下数据会被均匀的散布在中间，inode 会位于后方

create file /foo 
write file  /foo offset=0 size=1 
write file  /foo offset=1 size=1 
write file  /foo offset=2 size=1 
write file  /foo offset=3 size=1 

FINAL file system contents:
[   0 ] live checkpoint: 19 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ]      type:reg size:1 refs:1 ptrs: 8 -- -- -- -- -- -- -- 
[  10 ]      chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  11 ] live t0t0t0t0t0t0t0t0t0t0t0t0t0t0t0t0
[  12 ]      type:reg size:2 refs:1 ptrs: 8 11 -- -- -- -- -- -- 
[  13 ]      chunk(imap): 5 12 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  14 ] live k0k0k0k0k0k0k0k0k0k0k0k0k0k0k0k0
[  15 ]      type:reg size:3 refs:1 ptrs: 8 11 14 -- -- -- -- -- 
[  16 ]      chunk(imap): 5 15 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  17 ] live g0g0g0g0g0g0g0g0g0g0g0g0g0g0g0g0
[  18 ] live type:reg size:4 refs:1 ptrs: 8 11 14 17 -- -- -- -- 
[  19 ] live chunk(imap): 5 18 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

6.
> lfs.py -o -L c,/foo:w,/foo,0,4 -c -v
这种情况下所有的数据会位于相同的连续位置，读写性能更好（顺序性），为了做到这一点需要
使用写缓存。
create file /foo 
write file  /foo offset=0 size=4 

FINAL file system contents:
[   0 ] live checkpoint: 13 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ] live t1t1t1t1t1t1t1t1t1t1t1t1t1t1t1t1
[  10 ] live k2k2k2k2k2k2k2k2k2k2k2k2k2k2k2k2
[  11 ] live g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3
[  12 ] live type:reg size:4 refs:1 ptrs: 8 9 10 11 -- -- -- -- 
[  13 ] live chunk(imap): 5 12 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

7.
没有太大的区别，只是占用的空间大小不同而已，反正下一次写入会使用别的块
> lfs.py -L c,/foo:w,/foo,0,1 -c -v -o
create file /foo 
write file  /foo offset=0 size=1 

FINAL file system contents:
[   0 ] live checkpoint: 10 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ] live type:reg size:1 refs:1 ptrs: 8 -- -- -- -- -- -- -- 
[  10 ] live chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

> lfs.py -L c,/foo:w,/foo,7,1 -c -v -o
create file /foo 
write file  /foo offset=7 size=1 

FINAL file system contents:
[   0 ] live checkpoint: 10 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8 
[  10 ] live chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

8.
创建文件和目录都更新了其父目录 inode，且创建了其自身的 inode，不同的一点是创建目录还要
写入目录数据，而创建文件则不写入任何数据
> lfs.py -L c,/foo -c -v -o
create file /foo 
FINAL file system contents:
[   0 ] live checkpoint: 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ] live chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

> lfs.py -L d,/foo -c -v -o
create dir  /foo 
FINAL file system contents:
[   0 ] live checkpoint: 8 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live [.,1] [..,0] -- -- -- -- -- -- 
[   6 ] live type:dir size:1 refs:3 ptrs: 4 -- -- -- -- -- -- -- 
[   7 ] live type:dir size:1 refs:2 ptrs: 5 -- -- -- -- -- -- -- 
[   8 ] live chunk(imap): 6 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

9.
> lfs.py -L c,/foo:l,/foo,/bar:l,/foo,/goo -o -i -v -c
当创建链接时，被链接的 inode 更新引用计数，链接所在的目录更新其 inode 和目录内容
create file /foo 
[   0 ] live checkpoint: 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
...
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ] live chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 


link file   /foo /bar 
[   0 ] live checkpoint: 11 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
...
[   8 ] live [.,0] [..,0] [foo,1] [bar,1] -- -- -- -- 
[   9 ] live type:dir size:1 refs:2 ptrs: 8 -- -- -- -- -- -- -- 
[  10 ] live type:reg size:0 refs:2 ptrs: -- -- -- -- -- -- -- -- 
[  11 ] live chunk(imap): 9 10 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

10.
使用从 0 开始的 imap 号有助于减少 imap 大小，让整体结构更紧凑
> lfs.py -p c100 -n 10 -o -a s
create file /kg5 
create file /hm5 
create file /ht6 
create file /zv9 
create file /xr4 
create file /px9 
create file /gu5 
create file /kv6 
create file /wg3 
create file /og9 

FINAL file system contents:
[   0 ] live checkpoint: 43 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ]      [.,0] [..,0] [kg5,1] -- -- -- -- -- 
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ]      [.,0] [..,0] [kg5,1] [hm5,2] -- -- -- -- 
[   9 ]      type:dir size:1 refs:2 ptrs: 8 -- -- -- -- -- -- -- 
[  10 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  11 ]      chunk(imap): 9 6 10 -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  12 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] -- -- -- 
[  13 ]      type:dir size:1 refs:2 ptrs: 12 -- -- -- -- -- -- -- 
[  14 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  15 ]      chunk(imap): 13 6 10 14 -- -- -- -- -- -- -- -- -- -- -- -- 
[  16 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] -- -- 
[  17 ]      type:dir size:1 refs:2 ptrs: 16 -- -- -- -- -- -- -- 
[  18 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  19 ]      chunk(imap): 17 6 10 14 18 -- -- -- -- -- -- -- -- -- -- -- 
[  20 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] [xr4,5] -- 
[  21 ]      type:dir size:1 refs:2 ptrs: 20 -- -- -- -- -- -- -- 
[  22 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  23 ]      chunk(imap): 21 6 10 14 18 22 -- -- -- -- -- -- -- -- -- -- 
[  24 ] live [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] [xr4,5] [px9,6] 
[  25 ]      type:dir size:1 refs:2 ptrs: 24 -- -- -- -- -- -- -- 
[  26 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  27 ]      chunk(imap): 25 6 10 14 18 22 26 -- -- -- -- -- -- -- -- -- 
[  28 ]      [gu5,7] -- -- -- -- -- -- -- 
[  29 ]      type:dir size:2 refs:2 ptrs: 24 28 -- -- -- -- -- -- 
[  30 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  31 ]      chunk(imap): 29 6 10 14 18 22 26 30 -- -- -- -- -- -- -- -- 
[  32 ]      [gu5,7] [kv6,8] -- -- -- -- -- -- 
[  33 ]      type:dir size:2 refs:2 ptrs: 24 32 -- -- -- -- -- -- 
[  34 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  35 ]      chunk(imap): 33 6 10 14 18 22 26 30 34 -- -- -- -- -- -- -- 
[  36 ]      [gu5,7] [kv6,8] [wg3,9] -- -- -- -- -- 
[  37 ]      type:dir size:2 refs:2 ptrs: 24 36 -- -- -- -- -- -- 
[  38 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  39 ]      chunk(imap): 37 6 10 14 18 22 26 30 34 38 -- -- -- -- -- -- 
[  40 ] live [gu5,7] [kv6,8] [wg3,9] [og9,10] -- -- -- -- 
[  41 ] live type:dir size:2 refs:2 ptrs: 24 40 -- -- -- -- -- -- 
[  42 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  43 ] live chunk(imap): 41 6 10 14 18 22 26 30 34 38 42 -- -- -- -- -- 

> lfs.py -p c100 -n 10 -o -a r -o -v -c
create file /kg5 
create file /hm5 
create file /ht6 
create file /zv9 
create file /xr4 
create file /px9 
create file /gu5 
create file /kv6 
create file /wg3 
create file /og9 

FINAL file system contents:
[   0 ] live checkpoint: 52 38 -- -- -- 23 -- 13 53 -- -- 48 8 -- 33 -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ]      [.,0] [..,0] [kg5,205] -- -- -- -- -- 
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ] live chunk(imap): -- -- -- -- -- -- -- -- -- -- -- -- -- 6 -- -- 
[   9 ]      [.,0] [..,0] [kg5,205] [hm5,114] -- -- -- -- 
[  10 ]      type:dir size:1 refs:2 ptrs: 9 -- -- -- -- -- -- -- 
[  11 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  12 ]      chunk(imap): 10 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  13 ] live chunk(imap): -- -- 11 -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  14 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] -- -- -- 
[  15 ]      type:dir size:1 refs:2 ptrs: 14 -- -- -- -- -- -- -- 
[  16 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  17 ]      chunk(imap): 15 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  18 ]      chunk(imap): -- -- -- -- 16 -- -- -- -- -- -- -- -- -- -- -- 
[  19 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] -- -- 
[  20 ]      type:dir size:1 refs:2 ptrs: 19 -- -- -- -- -- -- -- 
[  21 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  22 ]      chunk(imap): 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  23 ] live chunk(imap): -- 21 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  24 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] [xr4,130] -- 
[  25 ]      type:dir size:1 refs:2 ptrs: 24 -- -- -- -- -- -- -- 
[  26 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  27 ]      chunk(imap): 25 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  28 ]      chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  29 ] live [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] [xr4,130] [px9,238] 
[  30 ]      type:dir size:1 refs:2 ptrs: 29 -- -- -- -- -- -- -- 
[  31 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  32 ]      chunk(imap): 30 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  33 ] live chunk(imap): -- -- -- -- -- -- -- -- -- -- -- -- -- -- 31 -- 
[  34 ]      [gu5,27] -- -- -- -- -- -- -- 
[  35 ]      type:dir size:2 refs:2 ptrs: 29 34 -- -- -- -- -- -- 
[  36 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  37 ]      chunk(imap): 35 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  38 ] live chunk(imap): -- -- -- -- 16 -- -- -- -- -- -- 36 -- -- -- -- 
[  39 ]      [gu5,27] [kv6,141] -- -- -- -- -- -- 
[  40 ]      type:dir size:2 refs:2 ptrs: 29 39 -- -- -- -- -- -- 
[  41 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  42 ]      chunk(imap): 40 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  43 ]      chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- -- 41 -- -- 
[  44 ]      [gu5,27] [kv6,141] [wg3,180] -- -- -- -- -- 
[  45 ]      type:dir size:2 refs:2 ptrs: 29 44 -- -- -- -- -- -- 
[  46 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  47 ]      chunk(imap): 45 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  48 ] live chunk(imap): -- -- -- -- 46 -- -- -- -- -- -- -- -- -- -- -- 
[  49 ] live [gu5,27] [kv6,141] [wg3,180] [og9,140] -- -- -- -- 
[  50 ] live type:dir size:2 refs:2 ptrs: 29 49 -- -- -- -- -- -- 
[  51 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[  52 ] live chunk(imap): 50 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  53 ] live chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- 51 41 -- -- 

11.
checkpoint 不能反映最新的状态，这可能导致崩溃恢复时丢失最新数据
采用前读技术找到最后的日志，可以部分的恢复数据。
> lfs.py -N -i -o -s 100 -o -c -v

INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ] live [.,0] [..,0] -- -- -- -- -- -- 
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

create file /us7 

[   4 ] live [.,0] [..,0] [us7,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ] live chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

write file  /us7 offset=4 size=0 

[   8 ] live type:reg size:4 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   9 ] live chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

write file  /us7 offset=7 size=7 

[  10 ] live i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0
[  11 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 10 
[  12 ] live chunk(imap): 5 11 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 

FINAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   1 ]      [.,0] [..,0] -- -- -- -- -- -- 
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- -- 
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   4 ] live [.,0] [..,0] [us7,1] -- -- -- -- -- 
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- -- 
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[   8 ]      type:reg size:4 refs:1 ptrs: -- -- -- -- -- -- -- -- 
[   9 ]      chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
[  10 ] live i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0
[  11 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 10 
[  12 ] live chunk(imap): 5 11 -- -- -- -- -- -- -- -- -- -- -- -- -- --

