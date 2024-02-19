int checkx(int *b, int y)
{
    int ok[10];
    int i;
    for (i = 0; i < 10; i = i + 1)
    {
        ok[i] = 0;
    }
    for (i = 0; i < 9; i = i + 1)
    {
        int cur;
        cur = b[9 * y + i];
        if (cur != 0)
        {
            if (ok[cur] == 1)
            {
                return 0;
            }
            ok[cur] = 1;
        }
    }
    return 1;
}

int checky(int *b, int x)
{
    int ok[10];
    int i;
    for (i = 0; i < 10; i = i + 1)
    {
        ok[i] = 0;
    }
    for (i = 0; i < 9; i = i + 1)
    {
        int cur;
        cur = b[9 * i + x];
        if (cur != 0)
        {
            if (ok[cur] == 1)
            {
                return 0;
            }
            ok[cur] = 1;
        }
    }
    return 1;
}

int check3x3(int *b, int y, int x)
{
    y = y - (y % 3);
    x = x - (x % 3);
    int ok[10];
    int i;
    int j;
    for (i = 0; i < 10; i = i + 1)
    {
        ok[i] = 0;
    }
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            int cur;
            cur = b[9 * (y + i) + x + j];
            if (cur != 0)
            {
                if (ok[cur] == 1)
                {
                    return 0;
                }
                ok[cur] = 1;
            }
        }
    }
    return 1;
}

int check(int *b)
{
    int y;
    int x;

    for (x = 0; x < 9; x = x + 1)
    {
        if (checky(b, x) == 0)
        {
            return 0;
        }
    }
    for (y = 0; y < 9; y = y + 1)
    {
        if (checkx(b, y) == 0)
        {
            return 0;
        }
    }
    for (x = 0; x < 3; x = x + 1)
        for (y = 0; y < 3; y = y + 1)
            if (check3x3(b, y * 3, x * 3) == 0)
            {
                return 0;
            }

    return 1;
}
int complete(int *b)
{
    int y;
    int x;
    for (y = 0; y < 9; y = y + 1)
    {
        for (x = 0; x < 9; x = x + 1)
        {
            if (b[9 * y + x] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
int show(int *b)
{
    int y;
    int x;
    for (y = 0; y < 9; y = y + 1)
    {
        for (x = 0; x < 9; x = x + 1)
        {
            printf("%d ", b[9 * y + x]);
        }
        printf("\n");
    }
    return 0;
}
int solve(int *b)
{
    int y;
    int x;
    int i;
    printf("\n");
    show(b);
    printf("\n");
    if (complete(b) == 1)
    {
        printf("complete!\n");
        show(b);
        return 1;
    }
    int c[81];
    for (i = 0; i < 81; i = i + 1)
    {
        c[i] = b[i];
    }
    for (y = 0; y < 9; y = y + 1)
    {
        for (x = 0; x < 9; x = x + 1)
        {
            if (c[9 * y + x] == 0)
            {
                int k;
                for (k = 1; k <= 9; k = k + 1)
                {
                    printf("trying %d at %d %d\n", k, y, x);
                    c[9 * y + x] = k;
                    if (check(c) == 1)
                    {
                        printf("ok\n");
                        int ret;
                        ret = solve(c);
                        if (ret == 1)
                        {
                            return 1;
                        }
                        
                    }
                }
            }
        }
    }
    return 0;
}

int input(int *b)
{
    int y;
    int x;
    char tmp;
    for (y = 0; y < 9; y = y + 1)
    {
        for (x = 0; x < 9; x = x + 1)
        {
            scanf("%c", &tmp);
            b[9 * y + x] = tmp - 48;
        }
        scanf("%c", &tmp);
    }
}

int main()
{
    int b[81];
    input(b);
    show(b);
    solve(b);
    return 0;
}
