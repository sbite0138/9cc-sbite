#include "9cc.h"
int label;
char **arg_reg_32;
char **arg_reg_64;

void gen_globals()
{
    Variable *var = globals;
    if (var == NULL)
        return;
    char *varname = calloc(128, sizeof(char));
    for (; var != NULL; var = var->next)
    {

        strncpy(varname, var->name, var->len);
        varname[var->len] = '\0';
        // fprintf(stderr, "!%s %d\n", varname, var->len);
        printf(".comm %s, %d\n", varname, var->size);
    }
}

void gen_strings()
{
    Str *cur = strings;
    if (cur == NULL)
        return;
    char *str = calloc(128, sizeof(char));
    for (; cur != NULL; cur = cur->next)
    {
        // fprintf(stderr, "strings : %s\n", cur->str);
        strncpy(str, cur->str, cur->len);
        str[cur->len] = '\0';
        printf(".LC%d:\n", cur->id);
        printf("  .string %s\n", str);
    }
    // exit(0);
}

void gen_ptr(Node *node)
{
    // l rax ,r rdi
    assert(node->type->ty == PTR);
    // print_type(node->lhs->type);
    // print_type(node->rhs->type);
    // これはINT+PTRみたいな部分のアセンブルになっていて（多分）、CHARはここに入らないという前提をおきます（おくので）（PTR+CHARはgccでも警告が出ます）
    if (node->lhs->type == INT)
    {
        assert(node->rhs->type->ty == PTR);
        printf("  imul rax,%d\n", type_size(node->rhs->type->base));
    }
    else
    {
        assert(node->lhs->type->ty == PTR);
        printf("  imul rdi,%d\n", type_size(node->lhs->type->base));
        //  fprintf(stderr, "%d\n", type_size(node->lhs->type));
    }
}

void gen_gval(Node *node)
{
    if (node->kind == ND_DEREF)
    {
        gen(node->target);
        return;
    }
    char *varname = calloc(128, sizeof(char));
    strncpy(varname, node->gvarname, node->gvarnamelen);
    printf("  lea rax,%s[rip]\n", varname);
    printf("  push rax\n");
}

void gen_lval(Node *node)
{
    if (node->kind == ND_DEREF)
    {
        gen(node->target);
        printf("#back\n");
        return;
    }
    else if (node->kind != ND_LVAR && node->kind != ND_GVAR)
    {
        error("代入の左辺値が変数ではありません:%d", node->kind);
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
    Variable *cur = locals;
    int argcnt = 0;
    char *name = calloc(128, sizeof(char));

    switch (node->kind)
    {
    case ND_FUNC:
        strncpy(name, node->funcname, node->funcnamelen);
        fprintf(stderr, "generate code for function %s\n", name);
        printf(".global %s\n", name);
        printf("%s:\n", name);
        printf("  push rbp\n");
        printf("  mov rbp, rsp\n");
        // rspが16の倍数でないと落ちます
        printf("  sub rsp, %d\n", locals->offset + 16 - (locals->offset % 16));
        // 最悪をします。ごめんなさい。
        // localsを終端まで数えることで、関数内に登場する変数の数を得ます。そこからargmunを引くことで、引数の変数がどこから始まるかを得ます。
        // とても汚いので、あとで直しましょう
        while (cur != NULL)
        {
            argcnt++;
            cur = cur->next;
        }
        argcnt -= node->argnum;
        argcnt--;
        // fprintf(stderr, "%d\n", argcnt);
        cur = locals;
        for (int i = 0; i < argcnt; i++)
        {
            cur = cur->next;
        }

        // localの情報を元に引数の読み込みをしたいのだけど、localは後に追加したものが先頭に来ている（つまり、localの先頭は一番最後の引数）ので、iを大きい方から回している
        for (int i = node->argnum - 1; i >= 0; i--)
        {
            printf("  mov rax,  rbp\n");
            printf("  sub rax,  %d\n", cur->offset);
            // print_type(cur->type);
            if (cur->type->ty == INT)
            {
                printf("  mov DWORD PTR[rax],  %s\n", arg_reg_32[i]);
            }
            else if (cur->type->ty == PTR)
            {
                printf("  mov [rax],  %s\n", arg_reg_64[i]);
            }
            cur = cur->next;
        }
        gen(node->rhs);
        printf("  mov rsp,rbp\n");
        printf("  pop rbp\n");
        printf("  ret\n");

        return;
    case ND_NUM:
        printf("  push %d\n", node->val);
        return;
    case ND_ADDR:
        if (node->target->kind == ND_LVAR)
        {
            // fprintf(stderr, "LVAR\n");
            gen_lval(node->target);
        }
        else
        {
            // fprintf(stderr, "GVAR\n");
            gen_gval(node->target);
        }
        return;
    case ND_DEREF:
        // printf("#ND DEREF\n");
        // deref_nest++;
        print_type(node->target->type);
        gen(node->target);
        // deref_nest--;
        printf("  pop rax\n");
        // fprintf(stderr, "%p\n", node->rhs->type->ptr_to);
        // 多分ここは*(a+INT)みたいな処理をアセンブルしていて、*(a+CHAR)みたいなのはgccでもWarnが出るので考えないことにします
        printf("#DEREF\n");
        if (node->type->ty == ARRAY)
        {
            printf("  #target is array. dereference is canceled. \n");
            printf("  push rax\n");
            return;
        }
        if (node->target->type->base->ty == INT)
        {
            printf("  mov eax, DWORD  PTR[rax]\n");
        }
        // charも必要ですね。それはそう
        else if (node->target->type->base->ty == CHAR)
        {
            printf("  movsx eax, BYTE  PTR[rax]\n");
        }
        else
        {
            printf("  mov rax, [rax]\n");
        }
        printf("#DEREF DONE\n");

        printf("  push rax\n");
        return;
    case ND_NOP:
        gen(node->rhs);
        // deref_nest--;
        //  printf("  pop rax\n");
        return;
    case ND_LVAR:
        gen_lval(node);
        printf("  pop rax\n");
        if (node->type->ty == INT)
        {
            printf("  mov eax, DWORD  PTR[rax]\n");
        }
        else if (node->type->ty == CHAR)
        {
            printf("  movsx eax, BYTE  PTR[rax]\n");
        }
        else if (node->type->ty == PTR)
        {
            printf("  #ON\n");
            printf("  mov rax,[rax]\n");
        }
        printf("  push rax\n");
        return;
    case ND_GVAR:
        gen_gval(node);
        printf("  pop rax\n");
        if (node->type->ty == INT)
        {
            printf("  mov eax, DWORD  PTR[rax]\n");
        }
        else if (node->type->ty == CHAR)
        {
            printf("  movsx eax, BYTE  PTR[rax]\n");
        }

        else if (node->type->ty == PTR)
        {
            printf("  #ON\n");
            printf("  mov rax,[rax]\n");
        }
        printf("  push rax\n");
        return;
    case ND_STR:
        printf("  mov rax, OFFSET FLAT:.LC%d\n", node->str->id);
        printf("  push rax\n");
        return;
    case ND_ASSIGN:
        // print_type(node->lhs->type);

        if (node->lhs->kind == ND_LVAR)
        {
            gen_lval(node->lhs);
        }
        else
        {
            // node->lhs->kindがND_DEREFの場合はgen_gval内で再びgenに飛ぶ
            gen_gval(node->lhs);
        }
        // printf("#GEN LEFT DONE\n");
        gen(node->rhs);
        // rdiを退避する(関数呼び出しの引数が格納されているかもしれないので)
        printf("  mov r9,rdi\n");

        printf("  pop rdi\n");
        printf("  pop rax\n");

        if (node->lhs->type->ty == INT)
        {
            printf("  mov DWORD PTR[rax], edi\n");
        }
        else if (node->lhs->type->ty == CHAR)
        {
            printf("  mov [rax], dil\n");
        }
        else
        {
            printf("  mov [rax], rdi\n");
        }
        printf("  push rdi\n");
        // rdiを復元する
        printf("  mov rdi,r9\n");
        return;
    case ND_CALL:
        // 普通にgen()した後にレジスタに代入ってすると、例えばf(1,f(2,3,4),5)みたいなときに壊れる（f(...）を実行するまでに2つの引数を保管する
        // 必要があるので（ほんまか？））ので、一旦全部genしてからforでレジスタにpopしていきます
        for (int i = 0; node_args; i++)
        {

            printf("#GEN ARG\n");
            gen(node_args->node);
            printf("#GEN ARG DONE\n");

            // printf("  pop rax\n");
            /*if (node_args->node->type->ty == INT)
            {
                printf("  mov %s, eax\n", arg_reg_32[i]);
            }
            else
            */
            node_args = node_args->next;
            // fprintf(stderr, "hoge");
        }
        node_args = node->args;
        // fprintf(stderr, "argnum:%d\n", node->argnum);
        for (int i = node->argnum - 1; i >= 0; i--)
        {
            printf("  pop %s\n", arg_reg_64[i]);
        }
        // fprintf(stderr, "done\n");

        strncpy(name, node->funcname, node->funcnamelen);
        printf("  mov al, 0\n");
        printf("  call %s\n", name);
        printf("  push rax\n");
        return;
    case ND_RETURN:
        printf("#RETURN\n");
        // fprintf(stderr, "%d\n", node->lhs->kind == ND_DEREF);
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
        gen(node->condition);
        printf("  pop rax\n");
        printf("  cmp rax,0 \n");
        printf("  je .Lend%03d\n", current_label);
        gen(node->true_statement);
        printf("  pop rax\n");
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");
        return;
    case ND_IFELSE:
        label++;
        current_label = label;
        gen(node->condition);
        printf("  pop rax\n");
        printf("  cmp rax,0 \n");
        printf("  je .Lelse%03d\n", current_label);
        gen(node->true_statement);
        printf("  pop rax\n");
        printf("  jmp .Lend%03d\n", current_label);
        printf(".Lelse%03d:\n", current_label);
        gen(node->false_statement);
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
        if (node->initialize != NULL)
        {
            // fprintf(stdout, ";gen lhs->lhs\n");
            gen(node->initialize);
            printf("  pop rax\n");
        }
        printf(".Lbegin%03d:\n", current_label);

        if (node->condition != NULL)
        {
            // fprintf(stdout, ";gen lhs->rhs\n");
            gen(node->condition);
            printf("  pop rax\n");
            printf("  cmp rax,0 \n");
            printf("  je .Lend%03d\n", current_label);
        }
        // fprintf(stdout, ";gen rhs->rhs\n");

        gen(node->statement);
        printf("  pop rax\n");

        if (node->update != NULL)
        {
            // fprintf(stdout, ";gen rhs->lhs\n");
            gen(node->update);
            printf("  pop rax\n");
        }
        printf("  jmp .Lbegin%03d\n", current_label);
        printf(".Lend%03d:\n", current_label);
        printf("  push 0xBEEF\n");

        return;
    case ND_BLOCK:
        while (node_block)
        {
            // fprintf(stderr, "%p\n", node_block);
            // fprintf(stderr, "%p\n", node_block->stmt_node);

            gen(node_block->stmt_node);
            printf("  pop rax\n");

            node_block = node_block->next;
        }
        printf("  push 0xBEEF\n");

        return;
    }
    gen(node->lhs);
    gen(node->rhs);
    // rdiを退避する(関数呼び出しの引数が格納されているかもしれないので)
    printf("  mov r9,rdi\n");
    printf("  pop rdi\n");
    printf("  pop rax\n");

    switch (node->kind)
    {

    case ND_ADD:
        // if (node->type->ty == PTR)
        //{
        //    gen_ptr(node);
        // }
        printf("  add rax, rdi\n");
        break;
    case ND_SUB:
        // if (node->type->ty == PTR)
        //{
        //    gen_ptr(node);
        // }
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
        printf("  cmp eax, edi\n");
        printf("  sete al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_NEQ:
        printf("  cmp eax, edi\n");
        printf("  setne al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LT:
        printf("  cmp eax, edi\n");
        printf("  setl al\n");
        printf("  movzb rax, al\n");
        break;
    case ND_LEQ:
        printf("  cmp eax, edi\n");
        printf("  setle al\n");
        printf("  movzb rax, al\n");
        break;
    }
    printf("  push rax\n");
    // rdiを復元する
    printf("  mov rdi,r9\n");
}
