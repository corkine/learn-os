1.
> fsck.py -D -s 1
inode bitmap 1000100110010001
inodes       [d a:0 r:4] [] [] [] [f a:-1 r:1] [] [] [d a:10 r:2] [d a:15 r:2] [] [] [f a:-1 r:3] [] [] [] [f a:-1 r:1] 
data bitmap  1000000000100001
data         [(.,0) (..,0) (m,7) (a,8) (s,11) (g,11)] [] [] [] [] [] [] [] [] [] [(.,7) (..,0) (m,15) (e,11)] [] [] [] [] [(.,8) (..,0) (r,4)]

/
    /m
        /m
        /e
    /a
        /r
    s
    g


2.
> fsck.py -S 1
inode bitmap 1100100010000010
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

空闲块检查：
inode #13 不一致
data 一致

3.
> fsck.py -S 3
inode bitmap 1100100010000110
inodes       [d a:0 r:4] p[f a:-1 r:1] [] [] w[d a:8 r:2] [] [] [] g[d a:6 r:2] [] [] [] [] m[f a:15 r:2] t[f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] g[(.,8) (..,0)] [] w[(.,4) (..,0) (p,1)] [] [] [] t[z] [] [] m[g] 

空闲块检查：
inode 和 data 均一致
inode 状态、引用和地址指针检查：
inodes#1 OK
inodes#2 OK
inodes#4 OK
inodes#8 OK
inodes#13 引用数 2 错误，只有一个引用

目录检查：
inodes#1 OK
inodes#4 OK
inodes#8 OK

> fsck.py -S 19
inode bitmap 1100100010000110
inodes       [d a:0 r:4] p[f a:-1 r:1] [] [] w[d a:8 r:2] [] [] [] g[d a:6 r:1] [] [] [] [] m[f a:15 r:1] t[f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] g[(.,8) (..,0)] [] w[(.,4) (..,0) (p,1)] [] [] [] t[z] [] [] m[g] 

inodes#8 引用计数错误，应该为 2

这两个错误都是引用计数错误，不过一个是文件，一个是目录，对于文件而言，引用计数错误的原因通常是硬链接部分失败，而目录不能硬链接
其错误可能是目录数据写入失败

4.
> fsck.py -S 5
inode bitmap 1100100010000110
inodes       [d a:0 r:4] p[f a:-1 r:1] [] [] w[d a:8 r:2] [] [] [] g[d a:6 r:2] [] [] [] [] m[f a:15 r:1] t[f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] g[(.,8) (y,0)] [] w[(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g] 

空闲块 OK
inode#0 OK
inode#1 OK
inode#4 OK
inode#8 目录错误，没有 (..,0) 条目

> fsck.py -S 38
inode bitmap 1100100010000110
inodes       [d a:0 r:4] p[f a:-1 r:1] [] [] w[d a:8 r:2] [] [] [] g[d a:6 r:2] [] [] [] [] m[f a:15 r:1] t[f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] g[(.,8) (..,0)] [] w[(.,4) (..,0) (b,1)] [] [] [] t[z] [] [] [g] 

inode#4 (b,1) 实际存在的是 (p,1) 
这里其实是检查不出来的，因为检查目录对应都是 OK 的，换言之，fsck 没有更多的信息证明 inode#1 存在的是 p 而不是 b

> fsck.py -S 642
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (w,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

data#0 的 (w,8) 与 (w,4) 冲突，一个符号不能指向两个目录 inodes，在目录检测时可以找到此问题
如何处理？找到那个空的目录删掉（如果另一个不为空的话），因为空目录不影响其它内容，如果两个都不为空，那么就要找一个目录内容少的对其进行迁移。

> fsck.py -S 642
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (w,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (p,1)] [] [] [] [z] [] [] [g]
data#0 的 w 指针冲突，data#8 缺少 (..,0)

5.
> fsck.py -S 6
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [d a:-1 r:1] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

inode#12 为目录，不过没有数据，和 inode bitmap 不一致

> fsck.py -S 13
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [f a:-1 r:1] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

inode#10 文件没有引用，和 inode bitmap 不一致
以 bitmap 为基准，删掉这些孤儿 inodes
或者分情况讨论，对于目录无法恢复的，删除，对于文件，查找是否存在引用，存在则更新 bitmap，反之则删除

实际上，这里通常采用两步策略：将 bitmap 改为和 inode 一致，然后在下一步处理引用，如果引用错误，再将 inode 删掉到 lost+found 中。

6.
> fsck.py -S 9
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [d a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

inode#13 是文件，却标记为了 d，在处理 inode 类型时发现，将其改为 f

7.
> fsck.py -S 15
inode bitmap 1100100010000110
inodes       [f a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

inode#0 是目录却标记成了 f，在处理 inode 类型时发现，将其改为 d

8.
> fsck.py -S 10
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,3) (p,1)] [] [] [] [z] [] [] [g]

inode#4 的 (..,3) 指向错误的 data（空），可以根据其正确父目录（根）的 (w,4) 更新为正确的 (..,0)

9.
> fsck.py -S 16
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:5 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

inode#13 指向空节点 data#5，将其删除

> fsck.py -S 20
inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:11 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] [] 
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g] 

inode#8 指向了空节点 data#11，将其删除

但是实际上，这里读到的是脏数据，是不知道是空节点的，这是所谓的文件系统一致但垃圾数据情况。