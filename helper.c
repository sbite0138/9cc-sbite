#include "9cc.h"

int calloc4(int** x, int a, int b, int c, int d)
{
    *x = calloc(4, sizeof(int));
    *(*x + 0) = a;
    *(*x + 1) = b;
    *(*x + 2) = c;
    *(*x + 3) = d;
    return 0;
}
int calloc1(int* x)
{
    //*x = calloc(1, sizeof(int));
    printf("%d\n", *x);
    *x = 1;
    printf("%d\n", *x);
    return 0;
}

int ret_42()
{
    return 42;
}

int print_ok()
{
    printf("OK\n");
    return 0;
}

int print_ng()
{
    printf("NG\n");
    return 0;
}

int avg(int a, int b)
{
    return (a + b) / 2;
}

int mulab(int a, int b)
{
    return a * b;
}

int print_num(int n)
{
    printf("%d\n", n);
    return 0;
}
int print_addr(int n)
{
    printf("%p\n", n);
    return 0;
}

int print_char(int n)
{
    printf("%c", n);
    return 0;
}

int print_prime()
{
    printf("prime\n");
    return 0;
}

int print_composite()
{
    printf("composite\n");
    return 0;
}
