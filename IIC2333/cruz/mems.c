/*
  Compile with:

  gcc -o mems mems.c

*/

#include <stdio.h>
#include <stdlib.h>

int b = 3;

int main(int argc, char *argv[]) {
    int x=3;
    int a=8;
    int c[4] = {0,1,2,3};
    int e[4] = {0,1,2,3};
    int d = 6;
    printf("sizeof(int): %d\n", sizeof(int));
    printf("Location of code        : %p\n", (void *)main);
    printf("Location of data        : %p\n", (void *)&b);
    printf("Location of heap        : %p\n", (void *)malloc(1));
    printf("Location of stack for x : %p\n", (void *)&x);
    printf("Location of stack for a : %p\n", (void *)&a);
    printf("Location of stack for c : %p\n", (void *)&c);
    printf("Location of stack for d : %p\n", (void *)&d);
    printf("Location of stack for e : %p\n", (void *)&e);
    return x+b*a - c[3];
}

