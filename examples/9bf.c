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

    while (code[pcindex] != 0)
    {
        if (code[pcindex] == '>')
        {

            memindex = memindex + 1;
            if (memindex == 3000)
            {
                memindex = 0;
            }
        }
        else if (code[pcindex] == '<')
        {
            memindex = memindex - 1;
            if (memindex == -1)
            {
                memindex = 2999;
            }
        }
        else if (code[pcindex] == '+')
        {
            memory[memindex] = memory[memindex] + 1;
            if (memory[memindex] == 256)
            {
                memory[memindex] = 0;
            }
        }
        else if (code[pcindex] == '-')
        {
            memory[memindex] = memory[memindex] - 1;
            if (memory[memindex] == -1)
            {
                memory[memindex] = 255;
            }
        }
        else if (code[pcindex] == '[')
        {
            if (memory[memindex] == 0)
            {

                int stack;
                stack = 1;
                while (stack != 0)
                {
                    pcindex = pcindex + 1;
                    if (code[pcindex] == ']')
                        stack = stack - 1;
                    if (code[pcindex] == '[')
                        stack = stack + 1;
                }
            }
        }
        else if (code[pcindex] == ']')
        {
            if (memory[memindex] != 0)
            {
                int stack;
                stack = 1;
                while (stack != 0)
                {
                    pcindex = pcindex - 1;
                    if (code[pcindex] == ']')
                        stack = stack + 1;
                    if (code[pcindex] == '[')
                        stack = stack - 1;
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

            char c;
            scanf(" %c", &c);

            memory[memindex] = c;
        }
        else if (code[pcindex] == '@')
        {
            int i;
            for (i = 0; i < 16; i = i + 1)
            {
                printf("%d ", memory[i]);
            }
            printf("\n", memory[i]);
        }
        else
        {
            printf("none\n");
        }
        pcindex = pcindex + 1;
    }
    return 0;
}