

struct foo {
    int x[42];
    int xx;
    char xxx;
    char* xxx;
    char** xxxx[128];
    char** xxxxx[128][64];
};

int main()
{
    int errnum;
    errnum = 0;
    struct foo bar;
    if (sizeof(bar) != 66741) {
        errnum = errnum + 1;
        printf("test1 faild (actual:%d expect:%d)\n", sizeof(bar), 66741);
    }
    if (errnum == 0) {
        printf("test passed!\n");
    } else {
        printf("test faild with %d error(s)!\n", errnum);
    }

    return 0;
}