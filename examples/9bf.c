int main()
{
    char code[4096];
    int memory[4096];
    int i;
    int pcindex;
    int memindex;
    pcindex = 0;
    memindex = 0;
    for (i = 0; i < 4096; i = i + 1)
    {
        memory[i] = 0;
    }
    scanf("%s", code);
    printf("%c", code[2]);
    while (code[pcindex] != 0)
    {
        printf("%c\n", code[pcindex]);
        if (code[pcindex] == ',')
        {
            printf("yay!\n");
        }
        if (code[pcindex] == '>')
        {

            memindex = memindex + 1;
        }
        else if (code[pcindex] == '<')
        {
            memindex = memindex - 1;
        }
        else if (code[pcindex] == '+')
        {
            memory[memindex] = memory[memindex] + 1;
            if (memory[memindex] == 256)
                memory[memindex] = 0;
        }
        else if (code[pcindex] == '-')
        {
            memory[memindex] = memory[memindex] - 1;
            if (memory[memindex] == -1)
                memory[memindex] = 255;
        }
        else if (code[pcindex] == '[')
        {
            if (memory[memindex] == 0)
            {
                while (code[pcindex] != ']')
                {
                    pcindex = pcindex + 1;
                }
            }
        }
        else if (code[pcindex] == ']')
        {
            if (memory[memindex] != 0)
            {
                while (code[pcindex] != '[')
                {
                    pcindex = pcindex - 1;
                }
            }
        }
        else if (code[pcindex] == '.')
        {

            char c;
            c = memory[memindex];
            printf("%c", c);
        }
        else if (code[pcindex] == ',')
        {

            printf("scanf\n");
            char c;
            scanf("%c", c);
            memory[memindex] = c;
        }
        else
        {
            printf("none\n");
        }
        pcindex = pcindex + 1;
    }
    return 0;
}