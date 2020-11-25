
void f(int *x)
{
    *x = 42;
}

int main()
{
    struct
    {
        int x;
        int y;
        char z;
    } foo;
    foo.x = 11;
    foo.y = 22;
    foo.z = '@';
    printf("%d %d %c\n", foo.x, foo.y, foo.z);
    f(&foo.x);
    printf("%d %d %c\n", foo.x, foo.y, foo.z);
    return 0;
}
