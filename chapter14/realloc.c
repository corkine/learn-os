#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vec
{
    int *start;
    int *now;
    int *end;
};

static struct vec vecs[100];

int set(int a, int b, int var)
{
    if (a > 100)
        return -1;
    struct vec v = vecs[a];
    if ((v.end - v.now) <= 0)
    {
        int *t = realloc(v.start, (v.end - v.start) * 2 * sizeof(int));
        if (t == NULL)
            return -1;
        v.end = v.start + (v.end - v.start) * 2;
    }
    *v.now++ = var;
    return 1;
}

int get(int a, int b, int *var)
{
    if (a > 100)
        return -1;
    struct vec v = vecs[a];
    if (b > (v.now - v.start))
        return -1;
    else
        *var = v.now[b];
    return 1;
}

int main()
{
}