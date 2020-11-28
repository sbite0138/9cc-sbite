struct box
{
    int empty;
    char *name;
    int password;
};
int main()
{
    struct box locker[10][10];
    locker[1][1].password = 1234;
}