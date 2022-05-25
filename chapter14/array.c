#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *a = malloc(sizeof(int) * 100);
    a[100] = 0;
}