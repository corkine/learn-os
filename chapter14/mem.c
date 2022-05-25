#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("HELLO WORLD\n");
    int *a = malloc(sizeof(int) * 10); 
    printf("size of int *: %d\n", sizeof(a)); //8 on x64
    int b[10]; 
    printf("size of int []: %d\n", sizeof(b)); //10
    char *c = "hello";
    char *d = malloc(sizeof(c) + 1);
    strcpy(d, c); //or just use strdup
    char *e = strdup(d);
    printf("c: %s, d: %s, e: %s\n", c, d, e);
    free(a);
    free(d);
    free(e);
}