#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int *a = malloc(sizeof(int) * 100);
  for (size_t i = 0; i < 100; i++) {
    a[i] = i * i;
  }
  free(a + 30);
}