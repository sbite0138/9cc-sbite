#include "9cc.h"
int label;
char **arg_reg;

void gen_lval(Node *node)
{
    if (node->kind != ND_LVAR)
    {
        error("代入の左辺値が変数ではありません");
    }
    printf("  mov rax,  rbp\n");
    printf("  sub rax,  %d\n", node->offset);
    printf("  push rax\n");
}
void gen(Node *node)
{

    int current_label;
    Block *node_block = node->block;
    Arg *node_args = node->args;

    char *name = calloc(128, sizeof(char));

    switch (node->kind)
    {
    case ND_NUM:
        printf("  push %d\n", node->val);
        return;
    case ND_LVAR:
        gen_lval(node);
        printf("  pop rax\n");
        printf("  mov rax,[rax]\n");
        printf("  push rax\n");
        return;
    case ND_ASSIGN:
        gen_lval(node->lhs);
        gen(node->rhs);
        printf("  pop rdi\n");
        printf("  pop rax\n");
        printf("  mov [rax], rdi\n");
        printf("  push rdi\n");
        return;
    case ND_CALL:
        for (int i = 0; node_args; i++)
        {

            gen(node_args->node);

            printf("  pop rax\n");

            printf("  mov %s, rax\n", arg_reg[i]);

            node_args = node_args->next;
            //fprintf(stderr, "hoge");
        }
        //fprintf(stderr, "done\n");

        strncpy(name, node->funcname, node->funcnamelen);
        printf("  call %s\n", name);
        printf("  push rax\n");
        return;
    case ND_RETURN:
        gen(node->lhs);
        printf("  pop rax\n");
        printf("  mov rsp, rbp\n");
        printf("  pop rbp\n");
        printf("  ret\n");
        return;

    /*
    stmtから変換される処理には、最後に結果をスタックにpushするもの(=,+,==など)と、本来はしないもの(for,while,{}など)がある。
    この2つがごちゃまぜになっていると、スタックがオーバーフローしたり、必要な情報までpopしたりする。
    そこで、stmtから変換される命令は、全て何らかの値をpushし、また、stmtをgen()したあとは、必ずpop raxを行うことにした。
    これ以降のコードに出てくる push 0xBEEFは、本来値をpushしない命令が仮にpushする値となっている。
    */
    case ND_IF:
        label++;
        current_label = label;
        gen(node->lhs);
        printf("  pop rax\n");
        printf("  cmp rax,0 \n");
        printf("  je .Lend%03d\n", current_label);
        gen(node->rhs);
        printf("  pop rax\n");
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");
        return;
    case ND_IFELSE:
        label++;
        current_label = label;
        gen(node->lhs);
        printf("  pop rax\n");
        printf("  cmp rax,0 \n");
        printf("  je .Lelse%03d\n", current_label);
        gen(node->rhs->lhs);
        printf("  pop rax\n");
        printf("  jmp .Lend%03d\n", current_label);
        printf(".Lelse%03d:\n", current_label);
        gen(node->rhs->rhs);
        printf("  pop rax\n");
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");
        return;
    case ND_WHILE:
        label++;
        current_label = label;
        printf(".Lbegin%03d:\n", current_label);
        gen(node->lhs);
        printf("  pop rax\n");
        printf("  cmp rax,0 \n");
        printf("  je .Lend%03d\n", current_label);
        gen(node->rhs);
        printf("  pop rax\n");
        printf("  jmp .Lbegin%03d\n", current_label);
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");
        return;
    case ND_FOR:
        label++;
        current_label = label;
        if (node->lhs->lhs != NULL)
        {
            //fprintf(stdout, ";gen lhs->lhs\n");
            gen(node->lhs->lhs);
            printf("  pop rax\n");
        }
        printf(".Lbegin%03d:\n", current_label);

        if (node->lhs->rhs != NULL)
        {
            //fprintf(stdout, ";gen lhs->rhs\n");
            gen(node->lhs->rhs);
            printf("  pop rax\n");
            printf("  cmp rax,0 \n");
            printf("  je .Lend%03d\n", current_label);
        }
        //fprintf(stdout, ";gen rhs->rhs\n");

        gen(node->rhs->rhs);
        printf("  pop rax\n");

        if (node->rhs->lhs != NULL)
        {
            //fprintf(stdout, ";gen rhs->lhs\n");
            gen(node->rhs->lhs);
            printf("  pop rax\n");
        }
        printf("  jmp .Lbegin%03d\n", current_label);
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");

        return;
    case ND_BLOCK:
        while (node_block)
        {
            //fprintf(stderr, "%p\n", node_block);
            //fprintf(stderr, "%p\n", node_block->stmt_node);

            gen(node_block->stmt_node);
            printf("pop rax\n");

            node_block = node_block->next;
        }
        printf("  push 0xBEEF\n");

        return;
    }
    gen(node->lhs);
    gen(node->rhs);
    printf("  pop rdi\n");
    printf("  pop rax\n");

    switch (node->kind)
    {

    case ND_ADD:
        printf("  add rax, rdi\n");
        break;
    case ND_SUB:
        printf("  sub rax, rdi\n");
        break;
    case ND_MUL:
        printf("  imul rax, rdi\n");
        break;
    case ND_DIV:
        printf("  cqo\n");
        printf("  idiv rdi\n");
        break;
    case ND_MOD:
        printf("  cqo\n");
        printf("  idiv rdi\n");
        printf("  mov rax, rdx\n");
        break;
    case ND_EQ:
        printf("  cmp rax, rdi\n");
        printf("  sete al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_NEQ:
        printf("  cmp rax, rdi\n");
        printf("  setne al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LT:
        printf("  cmp rax, rdi\n");
        printf("  setl al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LEQ:
        printf("  cmp rax, rdi\n");
        printf("  setle al\n");
        printf("  movzb rax, al\n");
        break;
    }
    printf("  push rax\n");
}
