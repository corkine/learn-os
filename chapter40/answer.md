1.
vsfs.py -s 17
➜  chapter40 git:(master) ✗ vsfs.py -s 17
ARG seed 17
ARG numInodes 8
ARG numData 8
ARG numRequests 10
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

mkdir u

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

touch a

inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1) (a,2)] [(.,1) (..,0)] [] [] [] [] [] [] 

rm a

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

mkdir z

inode bitmap  11100000
inodes        [d a:0 r:4] [d a:1 r:2] [d a:2 r:2] [] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (u,1) (z,2)] [(.,1) (..,0)] [(.,2) (..,0)] [] [] [] [] [] 

mkdir s

inode bitmap  11110000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0)] [(.,3) (..,0)] [] [] [] [] 

touch z/x

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

ln z/x u/b

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:2] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0) (b,4)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

rm u/b

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

vi z/x

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:4 r:1] [] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [v] [] [] [] 

touch u/b

inode bitmap  11111100
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:4 r:1] [f a:-1 r:1] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0) (b,5)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [v] [] [] []


2.
vsfs.py -s 21 -r
Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

mkdir("/o");

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

creat("/b");

inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0)] [] [] [] [] [] [] 

creat("/o/q");

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [] [] [] [] [] [] 

fd=open("/b", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [v] [] [] [] [] [] 

fd=open("/o/q", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [v] [e] [] [] [] [] 

creat("/o/j");

inode bitmap  11111000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3) (j,4)] [v] [e] [] [] [] [] 

unlink("/b");

inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11010000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [] [e] [] [] [] [] 

fd=open("/o/j", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:2 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [g] [e] [] [] [] [] 

creat("/o/x");

inode bitmap  11111000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [f a:3 r:1] [f a:2 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4) (x,2)] [g] [e] [] [] [] [] 

mkdir("/o/t");

inode bitmap  11111100
inodes        [d a:0 r:3] [d a:1 r:3] [f a:-1 r:1] [f a:3 r:1] [f a:2 r:1] [d a:4 r:2] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4) (x,2) (t,5)] [g] [e] [(.,5) (..,1)] [] [] [] 


3.
