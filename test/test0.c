int test0() { return 0; }
int test1() { return 101; }
int test2() { return 42; }
int test3() { return 42 + 42 - 40 - 40 - 1 - 1 - 1 - 1; }
int test4() { return 42 + 42 - 40 - 40 - 1 - 1 - 1 - 1; }
int test5() { return 12 + 34 - 5; }
int test6() { return 1 + 1; }
int test7() { return 5 + 6 * 7; }
int test8() { return 5 * (9 - 6); }
int test9() { return (3 + 5) / 2; }
int test10() { return 1 * (2 * (2 + 1 + 2 * (6 - 1))) / (6 / (2 + 1)); }
int test11() { return -10 + 14; }
int test12() { return +14 - 10; }
int test13() { return -(-(-(-3))); }
int test14() { return 1 == 1; }
int test15() { return 2 == 12; }
int test16() { return (1 + 1 - 2 + 1) == 1; }
int test17() { return 1 == ((1 == 2) + (-1 == -1)) == 1; }
int test18() { return 1 != 100; }
int test19() { return (1 + 2 + 3) != (1 * 2 * 3); }
int test20() { return (1 + 2 + 3 + 4) != (1 * 2 * 3 * 4); }
int test21() { return 2 < 3; }
int test22() { return 3 > 1; }
int test23() { return (3 > 1) == (1 < 3); }
int test24() { return 1 + 2 > 1 * 2; }
int test25() { return 1 * 2 * 3 < 1 + 2 + 3; }
int test26() { return 2 <= 3; }
int test27() { return 3 >= 1; }
int test28() { return (3 >= 1) == (1 <= 3); }
int test29() { return 1 + 2 >= 1 * 2; }
int test30() { return 2 * 1 * 2 * 3 / 2 <= 1 + 2 + 3; }
int test31()
{
    int a31;
    a31 = 1;
    return a31;
}
int test32()
{
    int a32;
    int b32;
    a32 = 1;
    b32 = 2;
    return a32 + b32;
}
int test33()
{
    int a33;
    int b33;
    int c33;
    a33 = 1;
    b33 = a33;
    c33 = a33 * b33 + a33;
    return c33 + 2;
}
int test34()
{
    int a34;
    int b34;
    int c34;
    a34 = 1;
    b34 = 2;
    c34 = 2 * (a34 == b34) + 3 * (a34 != b34);
    return c34;
}
int test35()
{
    int foo35;
    int b35a35r;
    int b35a35z35;
    foo35 = 1;
    b35a35r = 2;
    b35a35z35 = 2 * (foo35 == b35a35r) + 3 * (foo35 != b35a35r);
    return b35a35z35;
}
int test36()
{
    int OKTHISISAVERYLONGLONGLONGNAME_____10101010a36a36a36a36a36a36a36a36;
    OKTHISISAVERYLONGLONGLONGNAME_____10101010a36a36a36a36a36a36a36a36 = 100;
    return OKTHISISAVERYLONGLONGLONGNAME_____10101010a36a36a36a36a36a36a36a36;
}
int test37()
{
    int a37;
    int b37;
    int c37;
    a37 = 1;
    b37 = 2;
    c37 = 1 + b37 + a37 / 2;
    return 0;
}
int test38()
{
    int a38;
    int b38;
    int c38;
    a38 = 1;
    b38 = 2;
    c38 = 1 + b38 + a38 / 2;
    return c38;
}
int test39()
{
    int return0;
    return0 = 1;
    return0 = 2;
    return return0;
}
int test40()
{
    if (2 == 1)
        return 2;
    return 3;
}
int test41()
{
    if (1 == 1)
        return 2;
    return 3;
}
int test42()
{
    int a42;
    a42 = 10;
    if (a42 == 10)
        a42 = a42 * 10;
    return a42;
}
int test43()
{
    int a43;
    a43 = 11;
    if (a43 == 10)
        a43 = a43 * 10;
    return a43;
}
int test44()
{
    int a44;
    a44 = 1;
    if (a44 == 1)
        a44 = a44 + 1;
    if (a44 == 2)
        a44 = a44 + 1;
    if (a44 == 3)
        a44 = a44 + 1;
    if (a44 == 3)
        a44 = a44 + 1;
    return a44;
}
int test45()
{
    int a45;
    if (1 == 1)
        a45 = 1;
    else
        a45 = 2;
    return a45;
}
int test46()
{
    int a46;
    if (2 == 1)
        a46 = 1;
    else if (1 == 2)
        a46 = 2;
    else
        a46 = 3;
    return a46;
}
int test47()
{
    int a47;
    if (2 == 1)
        a47 = 1;
    else if (1 == 2)
        a47 = 2;
    else if (1 == 1)
        a47 = 3;
    else
        a47 = 4;
    return a47;
}
int test48() { return 9 % 6; }
int test49()
{
    int a49;
    int c49ount;
    a49 = 27;
    c49ount = 0;
    while (a49 != 1)
        if (a49 % 2 == 0)
            a49 = a49 / 2;
        else
            a49 = 3 * a49 + 1;
    return a49;
}
int test50()
{
    int a50;
    int sum;
    sum = 0;
    for (a50 = 1; a50 <= 10; a50 = a50 + 1)
        sum = sum + a50;
    return sum;
}
int test51()
{
    int a51;
    int sum;
    sum = 0;
    a51 = 1;
    for (; a51 <= 10; a51 = a51 + 1)
        sum = sum + a51;
    return sum;
}
int test52()
{
    int a52;
    int sum;
    sum = 0;
    a52 = 1;
    for (;; a52 = a52 + 1)
        if (a52 == 55)
            return a52;
    return 0;
}
int test53()
{
    int a53;
    int sum;
    sum = 0;
    a53 = 1;
    for (;;)
        if (a53 == 55)
            return a53;
        else
            a53 = a53 + 1;
    return 0;
}
int test54()
{
    int a54;
    int sum;
    sum = 0;
    a54 = 1;
    for (; a54 < 55;)
        if (0 == 55)
            return a54;
        else
            a54 = a54 + 1;
    return a54;
}
int test55()
{
    int a55;
    a55 = 0;
    int i;
    i = 0;
    for (i = 0; i < 65536 * 16; i = i + 1)
    {
        a55 = 0;
    }
    return 0;
}
int test56()
{
    int a56;
    int i;
    a56 = 0;
    i = 0;
    for (i = 0; i < 10; i = i + 1)
    {
        a56 = a56 + 1;
        a56 = a56 + 1;
        a56 = a56 + 1;
        a56 = a56 + 1;
        a56 = a56 + 1;
    }
    return a56;
}
int test57()
{
    int a57;
    int i;
    a57 = 0;
    i = 0;
    {
        {
            {
                {
                    {
                        {
                            {
                                {
                                    0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int test58()
{
    int a58;
    int c58ount;
    a58 = 27;
    c58ount = 0;
    while (a58 != 1)
    {
        if (a58 % 2 == 0)
        {
            a58 = a58 / 2;
        }
        else
        {
            a58 = 3 * a58 + 1;
        }
        c58ount = c58ount + 1;
    }
    return c58ount;
}
int test59()
{
    int a59;
    if (ret_42() == 42)
        a59 = ret_42();
    while (ret_42() != 42)
    {
        a59 = 1;
    }
    return a59;
}
int test60()
{
    int a60;
    a60 = 1;
    return (21 * a60);
}
int fib61(int n)
{
    if (n <= 2)
        return 1;
    return fib61(n - 1) + fib61(n - 2);
}
int test61() { return (fib61(32)) % 100; }
int sub62(int first, int sec62ond62) { return first - sec62ond62; }

int test62() { return sub62(16, 6); }
int sub63(int first, int sec63ond63) { return first - sec63ond63; }
int test63()
{
    int i;
    for (i = 0; i < 65536; i = i + 1)
        sub63(16, 6);
    return 0;
}
int test64()
{
    int x64;
    int *y64;
    x64 = 42;
    y64 = &x64;
    return *y64;
}
int test65()
{
    int x65;
    int y65;
    int *z65;
    x65 = 42;
    y65 = 1111;
    z65 = &y65 + 1;
    return *z65;
}
int test66()
{
    int x66;
    int *y66;
    y66 = &x66;
    *y66 = 3;
    return x66;
}
int test67()
{
    int x67;
    int *y67;
    int **z67;
    x67 = 20;
    y67 = &x67;
    *y67 = *y67 + 20;
    z67 = &y67;
    y67 = y67;
    return **z67 + 2;
}
int test68()
{
    int *p;
    calloc4(&p, 1, 2, 4, 8);
    int *q;
    q = p + 2;
    if (*q != 4)
        return 0;
    q = p + 3;
    return *q;
}
int test69() { return sizeof(1); }
int test70()
{
    int x70;
    return sizeof(x70);
}
int test71()
{
    int *x71;
    return sizeof(x71);
}
int test72()
{
    int *x72;
    return sizeof(sizeof(x72));
}
int test73()
{
    int *x73;
    calloc4(&x73, 1, 2, 3, 4);
    return *(x73 + 1);
}
int test74()
{
    int *x74;
    calloc4(&x74, 1, 2, 3, 4);
    return *(x74 + sizeof(x74) / 8);
}
int test75()
{
    int a75[30];
    *(a75 + 1) = 2;
    *a75 = 32;
    return *(a75 + 1) + *a75;
}
int test76()
{
    int *a76[30];
    int x76;
    int y76;
    x76 = 32;
    y76 = 10;
    *(a76 + 1) = &x76;
    *a76 = &y76;
    return **(a76 + 1) + **a76;
}
int test77()
{
    int a77[2];
    *a77 = 1;
    *(a77 + 1) = 2;
    int *p;
    p = a77;
    return *p + *(p + 1);
}
int test78()
{
    int a78[30];
    a78[3] = 2;
    a78[0] = 32;
    return a78[3] + a78[0];
}
int test79()
{
    int a79[30];
    int i;
    for (i = 0; i < 30; i = i + 1)
    {
        a79[i] = i * i;
    }
    return a79[3] + a79[2];
}
int test80()
{
    int x80;
    int a80[30];
    *(a80 + 5) = 2;
    return *(a80 + 5);
}
int test81()
{
    int a81[30];
    int i;
    for (i = 0; i < 30; i = i + 1)
    {
        a81[i] = i * i;
    }
    return a81[a81[2] + a81[1]];
}
int test82()
{
    int *x82;
    int y82;
    x82 = &y82;
    *x82 = 21;
    return y82;
}
int test83()
{
    int *a83[3];
    int *x83;
    int y83;
    x83 = &y83;
    a83[0] = x83;
    *a83[0] = 1;
    return y83;
}
int test84()
{
    int a84[30];
    int *x84;
    x84 = a84;
    *(x84 + 1) = 32;
    return a84[1];
}
int x85;
int test85() { return sizeof(x85); }
int *x86;
int test86() { return sizeof(x86); }
int *x87;
int test87() { return sizeof(sizeof(x87)); }
int *x88;
int test88()
{
    calloc4(&x88, 1, 2, 3, 4);
    return *(x88 + 1);
}
int a89[30];
int test89()
{
    *(a89 + 1) = 2;
    *a89 = 32;
    return *(a89 + 1) + *a89;
}
int *a90[30];
int y90;
int test90()
{
    int x90;
    x90 = 32;
    y90 = 10;
    *(a90 + 1) = &x90;
    *a90 = &y90;
    return **(a90 + 1) + **a90;
}
int a91[2];
int test91()
{
    *a91 = 1;
    *(a91 + 1) = 2;
    int *p;
    p = a91;
    return *p + *(p + 1);
}
int a92[30];
int test92()
{
    a92[3] = 2;
    a92[0] = 32;
    return a92[3] + a92[0];
}
int test93()
{
    int i;
    int a93[30];
    for (i = 0; i < 30; i = i + 1)
    {
        a93[i] = i * i;
    }
    return a93[3] + a93[2];
}
int x94;
int foo94()
{
    x94 = 42;
    return 0;
}
int b94a94r()
{
    int x94;
    x94 = 32;
    return 0;
}
int test94()
{
    foo94();
    b94a94r();
    return x94;
}
int *a95[3];
int x95;
int test95()
{
    a95[1] = &x95;
    *a95[1] = 32;
    return x95;
}
int *a96[3];
int x96;
int test96()
{
    *(a96 + 1) = &x96;
    **(a96 + 1) = 32;
    return x96;
}
int test97()
{
    char x97[3];
    x97[0] = -1;
    x97[1] = 2;
    int y97;
    y97 = 4;
    return x97[0] + y97;
}
char *c98;
int test98()
{
    char d98;
    c98 = &d98;
    *c98 = 32;
    return d98;
}
char c99[12];
int test99()
{
    char d99;
    *c99 = 32;
    return *c99;
}
int test100()
{
    char *s;
    s = "cat";
    return *(s + 1);
}
int test101()
{
    int a101[10];
    int *x101;
    x101 = a101;
    x101[2] = 42;
    return a101[2];
}
int foo102(int *x102) { x102[3] = 32; }

int test102()
{
    int a102[10];
    foo102(a102);
    return a102[3];
}
int foo103(int a103, int b103) { return a103 + b103; }

int test103() { return foo103(foo103(1, 2), foo103(foo103(32, 64), 4)); }
int b104a104r(int x104, int y104) { return x104 - y104; }
int foo104(int a104, int b104) { return a104 + b104; }
int test104() { return b104a104r(foo104(8, 2), foo104(b104a104r(10, 9), 4)); }
int test105()
{
    int a105[10][10];
    a105[3][3] = 3;
    a105[9][2] = 11;
    return a105[3][3] + a105[9][2];
}

int main()
{
    if (test0() != 0)
    {
        printf("test0() faild (actual:%d expect:%d)\n", test0(), 0);
    }
    if (test1() != 101)
    {
        printf("test1() faild (actual:%d expect:%d)\n", test1(), 101);
    }
    if (test2() != 42)
    {
        printf("test2() faild (actual:%d expect:%d)\n", test2(), 42);
    }
    if (test3() != 0)
    {
        printf("test3() faild (actual:%d expect:%d)\n", test3(), 0);
    }
    if (test4() != 0)
    {
        printf("test4() faild (actual:%d expect:%d)\n", test4(), 0);
    }
    if (test5() != 41)
    {
        printf("test5() faild (actual:%d expect:%d)\n", test5(), 41);
    }
    if (test6() != 2)
    {
        printf("test6() faild (actual:%d expect:%d)\n", test6(), 2);
    }
    if (test7() != 47)
    {
        printf("test7() faild (actual:%d expect:%d)\n", test7(), 47);
    }
    if (test8() != 15)
    {
        printf("test8() faild (actual:%d expect:%d)\n", test8(), 15);
    }
    if (test9() != 4)
    {
        printf("test9() faild (actual:%d expect:%d)\n", test9(), 4);
    }
    if (test10() != 13)
    {
        printf("test10() faild (actual:%d expect:%d)\n", test10(), 13);
    }
    if (test11() != 4)
    {
        printf("test11() faild (actual:%d expect:%d)\n", test11(), 4);
    }
    if (test12() != 4)
    {
        printf("test12() faild (actual:%d expect:%d)\n", test12(), 4);
    }
    if (test13() != 3)
    {
        printf("test13() faild (actual:%d expect:%d)\n", test13(), 3);
    }
    if (test14() != 1)
    {
        printf("test14() faild (actual:%d expect:%d)\n", test14(), 1);
    }
    if (test15() != 0)
    {
        printf("test15() faild (actual:%d expect:%d)\n", test15(), 0);
    }
    if (test16() != 1)
    {
        printf("test16() faild (actual:%d expect:%d)\n", test16(), 1);
    }
    if (test17() != 1)
    {
        printf("test17() faild (actual:%d expect:%d)\n", test17(), 1);
    }
    if (test18() != 1)
    {
        printf("test18() faild (actual:%d expect:%d)\n", test18(), 1);
    }
    if (test19() != 0)
    {
        printf("test19() faild (actual:%d expect:%d)\n", test19(), 0);
    }
    if (test20() != 1)
    {
        printf("test20() faild (actual:%d expect:%d)\n", test20(), 1);
    }
    if (test21() != 1)
    {
        printf("test21() faild (actual:%d expect:%d)\n", test21(), 1);
    }
    if (test22() != 1)
    {
        printf("test22() faild (actual:%d expect:%d)\n", test22(), 1);
    }
    if (test23() != 1)
    {
        printf("test23() faild (actual:%d expect:%d)\n", test23(), 1);
    }
    if (test24() != 1)
    {
        printf("test24() faild (actual:%d expect:%d)\n", test24(), 1);
    }
    if (test25() != 0)
    {
        printf("test25() faild (actual:%d expect:%d)\n", test25(), 0);
    }
    if (test26() != 1)
    {
        printf("test26() faild (actual:%d expect:%d)\n", test26(), 1);
    }
    if (test27() != 1)
    {
        printf("test27() faild (actual:%d expect:%d)\n", test27(), 1);
    }
    if (test28() != 1)
    {
        printf("test28() faild (actual:%d expect:%d)\n", test28(), 1);
    }
    if (test29() != 1)
    {
        printf("test29() faild (actual:%d expect:%d)\n", test29(), 1);
    }
    if (test30() != 1)
    {
        printf("test30() faild (actual:%d expect:%d)\n", test30(), 1);
    }
    if (test31() != 1)
    {
        printf("test31() faild (actual:%d expect:%d)\n", test31(), 1);
    }
    if (test32() != 3)
    {
        printf("test32() faild (actual:%d expect:%d)\n", test32(), 3);
    }
    if (test33() != 4)
    {
        printf("test33() faild (actual:%d expect:%d)\n", test33(), 4);
    }
    if (test34() != 3)
    {
        printf("test34() faild (actual:%d expect:%d)\n", test34(), 3);
    }
    if (test35() != 3)
    {
        printf("test35() faild (actual:%d expect:%d)\n", test35(), 3);
    }
    if (test36() != 100)
    {
        printf("test36() faild (actual:%d expect:%d)\n", test36(), 100);
    }
    if (test37() != 0)
    {
        printf("test37() faild (actual:%d expect:%d)\n", test37(), 0);
    }
    if (test38() != 3)
    {
        printf("test38() faild (actual:%d expect:%d)\n", test38(), 3);
    }
    if (test39() != 2)
    {
        printf("test39() faild (actual:%d expect:%d)\n", test39(), 2);
    }
    if (test40() != 3)
    {
        printf("test40() faild (actual:%d expect:%d)\n", test40(), 3);
    }
    if (test41() != 2)
    {
        printf("test41() faild (actual:%d expect:%d)\n", test41(), 2);
    }
    if (test42() != 100)
    {
        printf("test42() faild (actual:%d expect:%d)\n", test42(), 100);
    }
    if (test43() != 11)
    {
        printf("test43() faild (actual:%d expect:%d)\n", test43(), 11);
    }
    if (test44() != 4)
    {
        printf("test44() faild (actual:%d expect:%d)\n", test44(), 4);
    }
    if (test45() != 1)
    {
        printf("test45() faild (actual:%d expect:%d)\n", test45(), 1);
    }
    if (test46() != 3)
    {
        printf("test46() faild (actual:%d expect:%d)\n", test46(), 3);
    }
    if (test47() != 3)
    {
        printf("test47() faild (actual:%d expect:%d)\n", test47(), 3);
    }
    if (test48() != 3)
    {
        printf("test48() faild (actual:%d expect:%d)\n", test48(), 3);
    }
    if (test49() != 1)
    {
        printf("test49() faild (actual:%d expect:%d)\n", test49(), 1);
    }
    if (test50() != 55)
    {
        printf("test50() faild (actual:%d expect:%d)\n", test50(), 55);
    }
    if (test51() != 55)
    {
        printf("test51() faild (actual:%d expect:%d)\n", test51(), 55);
    }
    if (test52() != 55)
    {
        printf("test52() faild (actual:%d expect:%d)\n", test52(), 55);
    }
    if (test53() != 55)
    {
        printf("test53() faild (actual:%d expect:%d)\n", test53(), 55);
    }
    if (test54() != 55)
    {
        printf("test54() faild (actual:%d expect:%d)\n", test54(), 55);
    }
    if (test55() != 0)
    {
        printf("test55() faild (actual:%d expect:%d)\n", test55(), 0);
    }
    if (test56() != 50)
    {
        printf("test56() faild (actual:%d expect:%d)\n", test56(), 50);
    }
    if (test57() != 0)
    {
        printf("test57() faild (actual:%d expect:%d)\n", test57(), 0);
    }
    if (test58() != 111)
    {
        printf("test58() faild (actual:%d expect:%d)\n", test58(), 111);
    }
    if (test59() != 42)
    {
        printf("test59() faild (actual:%d expect:%d)\n", test59(), 42);
    }
    if (test60() != 21)
    {
        printf("test60() faild (actual:%d expect:%d)\n", test60(), 21);
    }
    if (test61() != 9)
    {
        printf("test61() faild (actual:%d expect:%d)\n", test61(), 9);
    }
    if (test62() != 10)
    {
        printf("test62() faild (actual:%d expect:%d)\n", test62(), 10);
    }
    if (test63() != 0)
    {
        printf("test63() faild (actual:%d expect:%d)\n", test63(), 0);
    }
    if (test64() != 42)
    {
        printf("test64() faild (actual:%d expect:%d)\n", test64(), 42);
    }
    if (test65() != 42)
    {
        printf("test65() faild (actual:%d expect:%d)\n", test65(), 42);
    }
    if (test66() != 3)
    {
        printf("test66() faild (actual:%d expect:%d)\n", test66(), 3);
    }
    if (test67() != 42)
    {
        printf("test67() faild (actual:%d expect:%d)\n", test67(), 42);
    }
    if (test68() != 8)
    {
        printf("test68() faild (actual:%d expect:%d)\n", test68(), 8);
    }
    if (test69() != 4)
    {
        printf("test69() faild (actual:%d expect:%d)\n", test69(), 4);
    }
    if (test70() != 4)
    {
        printf("test70() faild (actual:%d expect:%d)\n", test70(), 4);
    }
    if (test71() != 8)
    {
        printf("test71() faild (actual:%d expect:%d)\n", test71(), 8);
    }
    if (test72() != 4)
    {
        printf("test72() faild (actual:%d expect:%d)\n", test72(), 4);
    }
    if (test73() != 2)
    {
        printf("test73() faild (actual:%d expect:%d)\n", test73(), 2);
    }
    if (test74() != 2)
    {
        printf("test74() faild (actual:%d expect:%d)\n", test74(), 2);
    }
    if (test75() != 34)
    {
        printf("test75() faild (actual:%d expect:%d)\n", test75(), 34);
    }
    if (test76() != 42)
    {
        printf("test76() faild (actual:%d expect:%d)\n", test76(), 42);
    }
    if (test77() != 3)
    {
        printf("test77() faild (actual:%d expect:%d)\n", test77(), 3);
    }
    if (test78() != 34)
    {
        printf("test78() faild (actual:%d expect:%d)\n", test78(), 34);
    }
    if (test79() != 13)
    {
        printf("test79() faild (actual:%d expect:%d)\n", test79(), 13);
    }
    if (test80() != 2)
    {
        printf("test80() faild (actual:%d expect:%d)\n", test80(), 2);
    }
    if (test81() != 25)
    {
        printf("test81() faild (actual:%d expect:%d)\n", test81(), 25);
    }
    if (test82() != 21)
    {
        printf("test82() faild (actual:%d expect:%d)\n", test82(), 21);
    }
    if (test83() != 1)
    {
        printf("test83() faild (actual:%d expect:%d)\n", test83(), 1);
    }
    if (test84() != 32)
    {
        printf("test84() faild (actual:%d expect:%d)\n", test84(), 32);
    }
    if (test85() != 4)
    {
        printf("test85() faild (actual:%d expect:%d)\n", test85(), 4);
    }
    if (test86() != 8)
    {
        printf("test86() faild (actual:%d expect:%d)\n", test86(), 8);
    }
    if (test87() != 4)
    {
        printf("test87() faild (actual:%d expect:%d)\n", test87(), 4);
    }
    if (test88() != 2)
    {
        printf("test88() faild (actual:%d expect:%d)\n", test88(), 2);
    }
    if (test89() != 34)
    {
        printf("test89() faild (actual:%d expect:%d)\n", test89(), 34);
    }
    if (test90() != 42)
    {
        printf("test90() faild (actual:%d expect:%d)\n", test90(), 42);
    }
    if (test91() != 3)
    {
        printf("test91() faild (actual:%d expect:%d)\n", test91(), 3);
    }
    if (test92() != 34)
    {
        printf("test92() faild (actual:%d expect:%d)\n", test92(), 34);
    }
    if (test93() != 13)
    {
        printf("test93() faild (actual:%d expect:%d)\n", test93(), 13);
    }
    if (test94() != 42)
    {
        printf("test94() faild (actual:%d expect:%d)\n", test94(), 42);
    }
    if (test95() != 32)
    {
        printf("test95() faild (actual:%d expect:%d)\n", test95(), 32);
    }
    if (test96() != 32)
    {
        printf("test96() faild (actual:%d expect:%d)\n", test96(), 32);
    }
    if (test97() != 3)
    {
        printf("test97() faild (actual:%d expect:%d)\n", test97(), 3);
    }
    if (test98() != 32)
    {
        printf("test98() faild (actual:%d expect:%d)\n", test98(), 32);
    }
    if (test99() != 32)
    {
        printf("test99() faild (actual:%d expect:%d)\n", test99(), 32);
    }
    if (test100() != 97)
    {
        printf("test100() faild (actual:%d expect:%d)\n", test100(), 97);
    }
    if (test101() != 42)
    {
        printf("test101() faild (actual:%d expect:%d)\n", test101(), 42);
    }
    if (test102() != 32)
    {
        printf("test102() faild (actual:%d expect:%d)\n", test102(), 32);
    }
    if (test103() != 103)
    {
        printf("test103() faild (actual:%d expect:%d)\n", test103(), 103);
    }
    if (test104() != 5)
    {
        printf("test104() faild (actual:%d expect:%d)\n", test104(), 5);
    }
    if (test105() != 14)
    {
        printf("test105() faild (actual:%d expect:%d)\n", test105(), 14);
    }
    return 0;
}
