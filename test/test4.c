
struct foo
{
    int a[42];
    int b;
    char c;
    char *d;
    char **e[128];
    char **f[128][64];
};

int main()
{
    int errnum;
    errnum = 0;
    struct foo bar;
    if (sizeof(bar) != 66741)
    {
        errnum = errnum + 1;
        printf("test1 faild (actual:%d expect:%d)\n", sizeof(bar), 66741);
    }
    bar.b = 2;
    bar.c = 'A' + bar.b;
    if (bar.c != 'C')
    {
        errnum = errnum + 1;
        printf("test2 faild (actual:%d expect:%d)\n", bar.c, 'C');
    }
    bar.d = &bar.c;
    *bar.d = 'A';
    if (bar.c != 'A')
    {
        errnum = errnum + 1;
        printf("test2 faild (actual:%d expect:%d)\n", bar.c, 'C');
    }

    if (errnum == 0)
    {
        printf("test passed!\n");
    }
    else
    {
        printf("test faild with %d error(s)!\n", errnum);
    }

    return 0;
}