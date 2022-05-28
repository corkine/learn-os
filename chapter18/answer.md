1.
随着 VAS 增加，基于线性页表的 PT 等比增大
./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0 1024
./paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0 2048
./paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0 4096
随着 Page 变大，基于线性页表的 PT 等比减小
./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0 1024
./paging-linear-translate.py -P 2k -a 1m -p 512m -v -n 0 512
./paging-linear-translate.py -P 4k -a 1m -p 512m -v -n 0 256

2.
./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0
-u 为 0 全部是无效地址，不用计算
./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50
VPN 4 Offset 10

Page Table (from entry 0 down to the max size)
  [       0]   0x80000018 0b111000
  [       1]   0x00000000
  [       2]   0x00000000
  [       3]   0x8000000c 0b101100
  [       4]   0x80000009 0b101001
  [       5]   0x00000000
  [       6]   0x8000001d 0b111101
  [       7]   0x80000013 0b110011
  [       8]   0x00000000
  [       9]   0x8000001f 0b111111
  [      10]   0x8000001c 0b111100
  [      11]   0x00000000
  [      12]   0x8000000f 0b101111
  [      13]   0x00000000
  [      14]   0x00000000
  [      15]   0x80000008 0b101000

Virtual Address Trace
  VA 0x00003385 (decimal:    13189) --> 0b1100(12)  0b011111110000101 -> 16261
  VA 0x0000231d (decimal:     8989) --> 0b1000(8)   1100011101 non-valid
  VA 0x000000e6 (decimal:      230) --> 0b0000(0)   0b110000011100110 -> 24806
  VA 0x00002e0f (decimal:    11791) --> 0b1011(11)  1000001111 non-valid
  VA 0x00001986 (decimal:     6534) --> 0b0110(6)   0b111010110000110 -> 30086

3.
在默认有效比例下，前两个地址无效的概率更高，因为分页占据总 VAS 的比例太高，以至于丧失了分页的优势：
./paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1
./paging-linear-translate.py -P 8k -a 32k -p 1m -v -s 2
./paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3

4.
程序会出错
./paging-linear-translate.py -P 1m -a 256m -p 100m -v -s 3