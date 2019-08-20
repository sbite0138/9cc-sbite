#include <stdio.h>

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

int print_num(int n)
{
    printf("%d\n", n);
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
