int fib(int n)
{
    if (n <= 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    printf("%d\n", fib(32));
    return 0;
}