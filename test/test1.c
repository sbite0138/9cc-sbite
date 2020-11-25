int func()
{
    //this is test comment

    int x;
    x = -1; //this is test comment

    int y;
    y = -1; //this is test comment

    return x - y;
}
//this is test comment

int main()
{
    //this is test comment
    if (func() <= 0)
    {
        printf("passed!\n"); //this is test comment
    }
    else
    {
        printf("func() faild (actual:%d expect:%d)\n", func(), -1); //this is test comment
    }
    return 0; //this is test comment
}