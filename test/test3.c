
int test1()
{
    int x[10][10];
    int y[10][10];
    int hash;
    hash = 0;
    int p;
    p = 10007;
    int i;
    int j;
    int k;
    for (i = 0; i < 10; i = i + 1)
    {
        for (j = 0; j < 10; j = j + 1)
        {
            x[i][j] = i * 10 + j;
            y[i][j] = 0;
        }
    }
    for (i = 0; i < 10; i = i + 1)
    {
        for (j = 0; j < 10; j = j + 1)
        {
            for (k = 0; k < 10; k = k + 1)
            {
                y[i][j] = y[i][j] + x[i][k] * x[k][j];
            }
        }
    }
    for (i = 0; i < 10; i = i + 1)
    {
        for (j = 0; j < 10; j = j + 1)
        {
            hash = ((hash * p) % p + y[i][j]) % p;
        }
    }
    return hash;
}

int main()
{
    int errnum;
    errnum = 0;
    if (test1() != 1820)
    {
        errnum = errnum + 1;
        printf("test107() faild (actual:%d expect:%d)\n", test1(), 1820);
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