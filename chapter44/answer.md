1.
> ssd.py -T log -s 1 -n 10 -q
FTL   (empty)
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data                                                                                                                                      
Live                                                                                                                                      

cmd   0:: write(20,u) -> success

FTL    20:  0 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vEEEEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  u                                                                                                                                   
Live  +                                                                                                                                   

cmd   1:: write(52,M) -> success

FTL    20:  0  52:  1 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvEEEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM                                                                                                                                  
Live  ++                                                                                                                                  

cmd   2:: read(52) -> M

FTL    20:  0  52:  1 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvEEEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM                                                                                                                                  
Live  ++                                                                                                                                  

cmd   3:: write(60,0) -> success

FTL    20:  0  52:  1  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvEEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0                                                                                                                                 
Live  +++                                                                                                                                 

cmd   4:: write(57,e) -> success

FTL    20:  0  52:  1  57:  3  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  ++++                                                                                                                                

cmd 5:: trim(57) -> success

FTL    20:  0  52:  1  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  +++                                                                                                                                 

cmd   6:: read(52) -> M

FTL    20:  0  52:  1  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  +++                                                                                                                                 

cmd 7:: trim(52) -> success

FTL    20:  0  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  + +                                                                                                                                 

cmd   8:: read(20) -> u

FTL    20:  0  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  + +                                                                                                                                 

cmd   9:: read(20) -> u

FTL    20:  0  60:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvEEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  uM0e                                                                                                                                
Live  + + 


2.
> ssd.py -T log -s 2 -n 10 -C
FTL   (empty)
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data                                                                                                                                      
Live                                                                                                                                      

cmd   0:: write(58, F) -> success
cmd   1:: write(46, 9) -> success
cmd   2:: write(31, I) -> success
cmd   3:: trim(31) -> success
cmd   4:: write(35, g) -> success
cmd   5:: read(46) -> 9
cmd   6:: read(35) -> g
cmd   7:: write(44, e) -> success
cmd   8:: read(58) -> F
cmd   9:: write(79, F) -> success

FTL    35:  3  44:  4  46:  1  58:  0  79:  5 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvvvEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  F9IgeF                                                                                                                              
Live  ++ +++   

3.
> ssd.py -T log -s 2 -n 10 -r 20 -C
-r ??????????????????????????????
FTL   (empty)
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data                                                                                                                                      
Live                                                                                                                                      

cmd   0:: read(66) -> fail: uninitialized read
cmd   1:: write(53, j) -> success
cmd   2:: write(48, A) -> success
cmd   3:: read(53) -> j
cmd   4:: write(79, W) -> success
cmd   5:: write(35, g) -> success
cmd   6:: read(37) -> fail: uninitialized read
cmd   7:: read(35) -> g
cmd   8:: write(44, e) -> success
cmd   9:: read(53) -> j

FTL    35:  3  44:  4  48:  1  53:  0  79:  2 
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvvEEEEE iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii iiiiiiiiii 
Data  jAWge                                                                                                                               
Live  +++++        

4.
default erase time is 1000 microseconds,
program time is 40, and read time is 10
???????????????erase ?????????????????????????????????

> ssd.py -T log -s 1 -n 100 -S
Logical Operation Sums
  Write count 47 (0 failed)
  Read count  43 (0 failed)
  Trim count  10 (0 failed)

Times
  Erase time 5000.00
  Write time 1880.00
  Read time  430.00
  Total time 7310.00

> ssd.py -T log -s 1 -n 100 -E 10000 -S
Logical Operation Sums
  Write count 47 (0 failed)
  Read count  43 (0 failed)
  Trim count  10 (0 failed)

Times
  Erase time 50000.00
  Write time 1880.00
  Read time  430.00
  Total time 52310.00

> ssd.py -T log -s 1 -n 100 -W 400 -R 100  -S
Logical Operation Sums
  Write count 47 (0 failed)
  Read count  43 (0 failed)
  Trim count  10 (0 failed)

Times
  Erase time 5000.00
  Write time 18800.00
  Read time  4300.00
  Total time 28100.00

5.
??????????????????????????????????????????????????? erase ????????????????????????????????????????????????
??????????????????????????????
> ssd.py -T direct -s 1 -n 100 -W 40 -R 10 -E 1000 -S
  Logical Operation Sums
  Write count 47 (0 failed)
  Read count  43 (0 failed)
  Trim count  10 (0 failed)

Times
  Erase time 47000.00
  Write time 6080.00
  Read time  1570.00
  Total time 54650.00

> ssd.py -T log -s 1 -n 100 -W 40 -R 10 -E 1000 -S
Logical Operation Sums
  Write count 47 (0 failed)
  Read count  43 (0 failed)
  Trim count  10 (0 failed)

Times
  Erase time 5000.00
  Write time 1880.00
  Read time  430.00
  Total time 7310.00

6.
?????? 10 ??????????????????????????????????????????????????????????????? I/O)
> ssd.py -T log -s 1 -n 1000 -C -F -S
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vEEEEEEEEE EEEEEEEEEE EEEEEEEEEE vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv 
Data  gavah1S3Wq rbqvaQGF09 7IQ4qT0giU AGUaWGnR6y SLqZlVBzYv X                                WTA8ndnsFy GgY3ig15FP u1552a5iJE sfDid4X1ZI 
Live   +++++++ + + ++++ +++ +++++ ++++ ++++++ + + ++++++++++ +                                + + +   ++ ++++ +++     +     ++  ++ +++ +  

Logical Operation Sums
  Write count 786 (0 failed)
  Read count  398 (0 failed)
  Trim count  110 (0 failed)

Times
  Erase time 83000.00
  Write time 31440.00
  Read time  6920.00
  Total time 121360.00

7.
??????????????????????????????????????????????????????????????????????????????
> ssd.py -T log -s 1 -n 1000 -G 3 -C -F -S
Block 0          1          2          3          4          5          6          7          8          9          10         11         
Page  0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 0000000000 1111111111 1111111111 
      0000000000 1111111111 2222222222 3333333333 4444444444 5555555555 6666666666 7777777777 8888888888 9999999999 0000000000 1111111111 
      0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 
State vvvvvvvvvv vvvvvvvvvv vvvvvvvvvv EEEEEEEEEE vvvvvvvvvv vvvvvvEEEE EEEEEEEEEE EEEEEEEEEE vvvvvvvvvv EEEEEEEEEE EEEEEEEEEE vvvvvvvvvv 
Data  GfFXlVZiIQ W341vByJU7 5SYadzY91g            qQqEyvrh5D aGAvIX                           UGASLqaWFg                       0g34ZRqan0 
Live  ++++++++++ ++++++++++ ++++++++++            ++++++++++ ++++ +                           ++++++++++                       ++++++++++ 

Logical Operation Sums
  Write count 4186 (0 failed)
  Read count  398 (0 failed)
  Trim count  110 (0 failed)

Times
  Erase time 424000.00
  Write time 167440.00
  Read time  40920.00
  Total time 632360.00

8.
?????? -J ???????????? GC ??????????????????????????????????????????????????? erase ?????????????????????????????? 10 ?????? GC???10 ?????????????????? Block ??????
???????????? erase ?????????
> ssd.py -T log -n 1000 -C -J -S
  Erase time 87000.00
  Write time 33520.00
  Read time  6920.00
  Total time 127440.00
> ssd.py -T ideal -n 1000 -C -J -S
  Erase time 0.00
  Write time 20800.00
  Read time  3740.00
  Total time 24540.00
> ssd.py -T direct -n 1000 -C -J -S
  Erase time 520000.00
  Write time 177520.00
  Read time  47320.00
  Total time 744840.00

????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????

9.
80 ??????20 ???????????????????????????????????????????????? direct ?????????????????????????????????????????????????????? 10 ???
> ssd.py -T log -K 80/20 -n 1000 -C -S
Logical Operation Sums
  Write count 587 (0 failed)
  Read count  380 (0 failed)
  Trim count  100 (0 failed)

Times
  Erase time 62000.00
  Write time 23480.00
  Read time  4470.00
  Total time 89950.00
> ssd.py -T direct -K 80/20 -n 1000 -C -S
Logical Operation Sums
  Write count 520 (0 failed)
  Read count  380 (0 failed)
  Trim count  100 (0 failed)

Times
  Erase time 520000.00
  Write time 173880.00
  Read time  46660.00
  Total time 740540.00

> ssd.py -T log -k 100 -K 20/80 -J -n 1000 -C -S
????????? 100 ?????????????????????????????????20/80 ??????????????????gc 
??????????????????????????????????????????????????? SSD ?????????????????????????????? GC
????????????????????????????????????????????????????????????????????????