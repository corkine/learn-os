1.
> ./paging-policy.py -s 0 -n 10 --policy=LRU
cache size 3
Access: 8  Miss 8
Access: 7  Miss 7 8
Access: 4  Miss 4 7 8
Access: 2  Miss 2 4 7, no 8
Access: 5  Miss 5 2 4, no 7
Access: 4  Hint 4 5 2
Access: 7  Miss 7 4 5, no 2
Access: 3  Miss 3 7 4, no 5
Access: 4  Hint 4 3 7
Access: 5  Miss 5 4 3, no 7

> ./paging-policy.py -s 0 -n 10 --policy=OPT
all: 2 3 4 5 7 8
Access: 8  Miss 8
Access: 7  Miss 7 8
Access: 4  Miss 4 7 8
Access: 2  Miss 2 4 7, no 8
Access: 5  Miss 5 4 7, no 2
Access: 4  Hint 5 4 7
Access: 7  Hint 5 4 7
Access: 3  Miss 3 5 4
Access: 4  Hint 3 5 4 
Access: 5  Hint 3 5 4

2.
FIFO, Miss All 只需要在撑爆内存后每次都新加上次驱逐出去的页
> ./paging-policy.py --cachesize=5 --addresses=0,1,2,3,4,5,0,1,2,3,4 --policy=FIFO

LRU 一样的全 Miss
> ./paging-policy.py --cachesize=5 --addresses=0,1,2,3,4,5,0,1,2,3,4 --policy=LRU

MRU 很有意思，在撑爆内存之后，每次替换掉最近使用的后，再将其加回来，循环往复就 Miss All
> ./paging-policy.py --cachesize=5 --addresses=0,1,2,3,4,5,4,5,4,5,4 --policy=MRU