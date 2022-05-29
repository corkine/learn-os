1.
不论任何级别的页表，都只需要一个寄存器，因为它是通过每级递归查找的
2.
./paging-multilevel-translate.py -s 0
                                                       15
page  33: 7f 7f 7f 7f 7f 7f 7f 7f b5 7f 9d 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f f6 b1 7f 7f 7f 7f
page  53: 0f 0c 18 09 0e 12 1c 0f 08 17 13 07 1c 1e 19 1b 09 16 1b 15 0e 03 0d 12 1c 1d 0e 1a 08 18 11 00 
page  78: 0e 02 17 1b 1c 1a 1b 1c 10 0c 15 08 19 1a 1b 12 1d 11 0d 14 1e 1c 18 02 12 0f 13 1a 07 16 03 06
page  84: 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 94 7f 7f 7f 7f 7f ce 
page  86: 7f 7f 7f 7f 7f 7f 7f c5 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f 7f ca 7f 7f ee 7f 7f 7f 7f 7f 7f 7f 7f
page 108: 83 fe e0 da 7f d4 7f eb be 9e d5 ad e4 ac 90 d6 92 d8 c1 f8 9f e1 ed e9 a1 e8 c7 c2 a9 d1 db ff 
32 * 8 = 256

PDBR: 108  (decimal) [This means the page directory is held in this page]
VAS: 32K, Page 32B, 1024 Pages:
VA:  10 VPN + 5 Offset
PAS: 128 Pages
PA:  7 PFN + 5 Offset
PTE: ValidBit | PFN7, total 1B -> 1 Page: 32 PTE
2-level PageTable 1024 Pages -> 32PDE -> 1PDE: 32PTE
10 VPN -> 5PDIndex + 5PTIndex

Virtual Address 611c: 0b11000/24 01000/ 8 11100 97 0 -> a1:161/0b10100001@v+33 -> b5:181/0b10110101@v+0b0110101 11100 -> 0x6bc -> 08
Virtual Address 3da8: 0b01111/15 01101/13 01000 61 5 -> d6:214/0b11010110@v+86 -> 7f:127/0b01111111@not-valid
Virtual Address 17f5: 0b00101/ 5 11111/31 10101 23 7 -> d4:212/0b11010100@v+84 -> ce:206/0b11001110@v+0b1001110 10101 -> 0x9d5 -> 1c

3.
只要查页表，页表肯定位于内存中，而非交换分区中，其会导致大量的缓存命中。