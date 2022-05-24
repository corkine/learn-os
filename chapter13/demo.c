#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    int a = 3;
    printf("pointer of code %p\n", (void *) main);
    printf("pointer of heap %p\n", (void *) malloc(1));
    printf("ponter of stack %p\n", (void *) &a);
    //pointer of code 0x4005d6
    //pointer of heap 0x23376b0
    //ponter of stack 0x7ffe2b1e980c
    return 0;
}