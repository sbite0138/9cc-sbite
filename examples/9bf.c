int main()
{
    char code[18192];
    int memory[18192];
    int i;
    int pcindex;
    int memindex;
    pcindex = 0;
    memindex = 0;
    for (i = 0; i < 18192; i = i + 1)
    {
        memory[i] = 0;
    }
    scanf("%s", code);
    while (code[pcindex] != 0)
    {
        if (code[pcindex] == '>')
        {

            memindex = memindex + 1;
            if (memindex == 18192)
            {
                memindex = 0;
            }
        }
        else if (code[pcindex] == '<')
        {
            memindex = memindex - 1;
            if (memindex == -1)
            {
                memindex = 18191;
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
            printf("\n");
        }
        else
        {
        }
        pcindex = pcindex + 1;
    }
    return 0;
}