#include <stdio.h>
int main()
{
    char code[4096];
    int ok[8192];
    scanf("%s", code);
    int label;
    int i;
    printf(".LC0:\n");
    printf("  .string \"%%d\"\n");
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("    push rbp\n");
    printf("    mov rbp,rsp\n");
    printf("    sub rsp, 8192\n");
    printf("    mov rax, rbp\n");

    i = 0;
    label = 0;
    while (code[i] != 0)
    {
        if (code[i] == '>')
        {
            printf("    add rax, 1\n");
        }
        else if (code[i] == '<')
        {
            printf("    sub rax, 1\n");
        }
        else if (code[i] == '+')
        {
            printf("    mov dil,[rax]\n");
            printf("    add dil, 1\n");
            printf("    mov [rax],dil\n");
        }
        else if (code[i] == '-')
        {
            printf("    mov dil,[rax]\n");
            printf("    sub dil, 1\n");
            printf("    mov [rax],dil\n");
        }
        else if (code[i] == '[')
        {
            printf("    cmp BYTE PTR [rax],0\n");
            printf("    je .LEND%d\n", label);
            printf(".LBEGIN%d:\n", label);
            label = label + 1;
        }
        else if (code[i] == ']')
        {
            label = label - 1;
            printf("    cmp BYTE PTR[rax],0\n");
            printf("    jne .LBEGIN%d\n", label);
            printf(".LEND%d:\n", label);
        }
        else if (code[i] == '.')
        {
            printf("    mov rdi, OFFSET FLAT:.LC0\n");
            printf("    movsx rsi, BYTE  PTR[rax]\n");
            printf("    mov al, 0\n");
            printf("    call printf\n");
        }
        else if (code[i] == ',')
        {
        }
        i = i + 1;
    }
    printf("    mov rsp,rbp\n");
    printf("    pop rbp\n");
    printf("    ret\n");

    return 0;
}