int func()
{
    int x;
    x = -1;
    int y;
    y = -1;
    return x - y;
}

int main()
{
    //hjisaasdf
    //asdasdf
    if (func() <= 0) {
        printf("passed!\n");
    } else {
        printf("func() faild (actual:%d expect:%d)\n", func(), -1);
    }
    return 0;
}