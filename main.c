#include "9cc.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        exit(1);
    }
    user_input = argv[1];
    //locals = calloc(1, sizeof(LVar));
    //locals->offset = 0;
    token = tokenize(argv[1]);
    //fprintf(stderr, "tokenize() done\n");
    arg_reg = (char **)calloc(6, 16 * sizeof(char));
    arg_reg[0] = "rdi";
    arg_reg[1] = "rsi";
    arg_reg[2] = "rdx";
    arg_reg[3] = "rcx";
    arg_reg[4] = "r8";
    arg_reg[5] = "r9";

    program();
    //fprintf(stderr, "program() done\n");
    printf(".intel_syntax noprefix\n");

    int i = 0;
    for (; code[i]; i++)
    {
        locals = func_variables[i];
        gen(code[i]);

        //fprintf(stderr, "gen(code[%d]) done\n", i);
        //printf("  pop rax\n");
    }
    return 0;
}