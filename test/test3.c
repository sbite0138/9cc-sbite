
int test107()
{
    int x[10][10][10];
    x[0][0][0] = 42;
    printf("%d\n", ***x);
}

int main()
{
    printf("%d\n", test107());
    printf("%d\n", test107());
    printf("%d\n", test107());
    printf("%d\n", test107());

    return 0;
}