int array;
int garray2;

int main()
{

    int errnum;
    errnum = 0;
    array = 32;
    if (array != 32)
    {
        errnum = errnum + 1;
        printf("test1 faild (actual:%d expect:%d)\n", array, 32);
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