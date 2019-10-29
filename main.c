#include "9cc.h"

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 2)
    {
        fprintf(stderr, "Usage: %s (-e filiname | source code)\n", argv[0]);
        exit(1);
    }
    if (argc == 2)
    {
        user_input = read_file(argv[1]);
    }
    else
    {

        if (strcmp(argv[1], "-e") != 0)
        {
            fprintf(stderr, "Unknown option: %s\n", argv[1]);
            exit(1);
        }

        user_input = argv[2];
    }
    //fprintf(stderr, "program: %s\n", user_input);
    //locals = calloc(1, sizeof(LVar));
    //locals->offset = 0;
    token = tokenize(user_input);
    //fprintf(stderr, "tokenize() done\n");

    arg_reg_32 = (char **)calloc(6, 16 * sizeof(char));
    arg_reg_32[0] = "edi";
    arg_reg_32[1] = "esi";
    arg_reg_32[2] = "edx";
    arg_reg_32[3] = "ecx";
    arg_reg_32[4] = "r8d";
    arg_reg_32[5] = "r9d";

    arg_reg_64 = (char **)calloc(6, 16 * sizeof(char));
    arg_reg_64[0] = "rdi";
    arg_reg_64[1] = "rsi";
    arg_reg_64[2] = "rdx";
    arg_reg_64[3] = "rcx";
    arg_reg_64[4] = "r8";
    arg_reg_64[5] = "r9";

    program();
    //   fprintf(stderr, "program() done\n");

    bool debug = true;
    if (debug == true)
    {
        FILE *fp = fopen("ast.dot", "w");
        fprintf(fp, "digraph G {\n");
        for (int i = 0; code[i]; i++)
            dumpAST(fp, code[i]);
        fprintf(fp, "}\n");
        fclose(fp);
        //return 0;
    }
    gen_globals();
    gen_strings();
    //return 0;
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