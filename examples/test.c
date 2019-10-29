int main()
{
    int x[3][3];
    int y[3][3];
    int z[3][3];
    int i;
    int j;
    int k;
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            x[i][j] = i * 3 + j;
            y[i][j] = -i * 3 - j;
        }
    }
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            z[i][j] = 0;
            for (k = 0; k < 3; k = k + 1)
            {
                z[i][j] = z[i][j] + x[i][k] * y[k][j];
            }
        }
    }
    printf("z=\n");
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            printf("%3d ", z[i][j]);
        }
        printf("\n");
    }
    return 0;
}