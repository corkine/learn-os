#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *a = "Hello";
    char *b = malloc(strlen(a) + 1);
    strcpy(b, a);
    printf("a is %s, b is %s\n", a, b);
}