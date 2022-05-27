1.
# ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> 01 101100     seg1 to-top:44, to-bottom:20 = 20 492
  VA  1: 0x00000061 (decimal:   97) --> 01 100001     seg1 to-top:33, to-bottom:31 > 20 seg-fault
  VA  2: 0x00000035 (decimal:   53) --> 00 110101     seg0 seg-fault
  VA  3: 0x00000021 (decimal:   33) --> 00 100001     seg0 seg-fault
  VA  4: 0x00000041 (decimal:   65) --> 01 000001     seg1 to-top:1, to-bottom:63 > 20 seg-fault

# ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> 00 010001 seg0 17
  VA  1: 0x0000006c (decimal:  108) --> 01 101100 seg1 to-top:44, to-bottom:20 = 20 492
  VA  2: 0x00000061 (decimal:   97) --> 01 100001 seg1 to-top:33, to-bottom:31 > 20 seg-fault
  VA  3: 0x00000020 (decimal:   32) --> 00 100000 seg0 seg-fault
  VA  4: 0x0000003f (decimal:   63) --> 00 111111 seg0 seg-fault

# ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> 01111010 seg1 58 - 64 + 512 = 506
  VA  1: 0x00000079 (decimal:  121) --> 01111001 seg1 57 - 64 + 512 = 505
  VA  2: 0x00000007 (decimal:    7) --> 00000111 seg0 7
  VA  3: 0x0000000a (decimal:   10) --> 00001010 seg0 10
  VA  4: 0x0000006a (decimal:  106) --> 01101010 seg1 42 - 64 > 20 seg-fault


2.
seg0 max virtual-address is 20
seg1 min virtual-address is 512 - 20 = 492
min illegal address is 20
max illegal address is 492
# ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -A 499 -c

3.
# ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2

4.
随机地址是通过 a 生成的，即保证 b 和 B 以及 l 和 L 使得两个分区占据 10% 的 a 空间即可。即 x + y = 0.1 * a
# ./segmentation.py -a a -p p --b0 0 --l0 x --b1 a --l1 y

5.
只要让 L 和 l 为 0 即可让所有地址失效。