1.
`malloc.py -n 10 -H 0 -p BEST -s 0`
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3)  1000
[1003, size 97]

Free(ptr[0]) 1000
[1000, size 3] [1003, size 97]

ptr[1] = Alloc(5)  1003
[1000, size 3] [1008, size 92]

Free(ptr[1]) 1003
[1000, size 3] [1003, size 5] [1008, size 92]

ptr[2] = Alloc(8)  1008
[1000, size 3] [1003, size 5] [1016, size 84]

Free(ptr[2]) 1008
[1000, size 3] [1003, size 5] [1008, size 8] [1016, size 84]

ptr[3] = Alloc(8)  1008
[1000, size 3] [1003, size 5] [1016, size 84]

Free(ptr[3]) 1008
[1000, size 3] [1003, size 5] [1008, size 8] [1016, size 84]

ptr[4] = Alloc(2)  1000
[1002, size 1] [1003, size 5] [1008, size 8] [1016, size 84]

ptr[5] = Alloc(7)  1008
[1002, size 1] [1003, size 5] [1015, size 1] [1016, size 84]

每次都需要遍历整个列表查找最优解，且碎片还是增多了

2.
`malloc.py -n 10 -H 0 -p WORST -s 0`
同上，小碎片更多了

3.
`malloc.py -n 10 -H 0 -p FIRST -s 0`
查找速度变快了

4.
`malloc.py -n 10 -H 0 -s 0 -p FIRST -l ADDRSORT`
FIRST 模式下：
    ADDRSORT 有助于合并，
    SIZESORT+ 会尽力将大块分割，类似于快速版本的 WORST
    SIZESORT- 会导致优先填充小块，类似于快速版本的 BEST
WORST 和 BEST 模式下：
    每次都需要遍历，各种排序没有任何作用

5.
`malloc.py -H 0 -p FIRST -s 0 -n 1000`
`malloc.py -H 0 -p FIRST -s 0 -n 1000 -C`
随机分配数量越来越大，导致小块越来越多以至于内部碎片无法利用
如果使用了合并，那么效果会大大改观，几乎没有内部碎片。当需要合并时
列表的排序跟策略有关，FIRST 模式下列表 ADDRSORT 排序会加速合并。

6.
`malloc.py -H 0 -p FIRST -s 0 -n 10 -P 50`
一半分配一半释放，最平常的情况，也是最容易导致碎片的情况
`malloc.py -H 0 -p FIRST -s 0 -n 10 -P 100`
全部都是分配，不论采用哪种方式，表现都很简单，没有任何碎片，无需合并
`malloc.py -H 0 -p FIRST -s 0 -n 10 -P 0`
程序出错，不能为 0，一份分配必定最多有一份回收，回收比例不可能高于分配比例

7.
要生成高度碎片化的空闲空间，只需要每次分配时都造成内部碎片且此内部碎片不足以下一次分配使用，
一种简单的策略就是一次分配一次回收，每次递增分配：
`malloc.py -H 0 -p FIRST -l ADDRSORT -A +1,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5`
[ Size 6 ]: 
    [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] 
    [ addr:1006 sz:4 ] [ addr:1010 sz:5 ] 
    [ addr:1015 sz:6 ] [ addr:1021 sz:79 ]