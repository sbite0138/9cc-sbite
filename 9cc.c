#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef enum
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF
} TokenKind;

typedef struct Token Token;

struct Token
{
    TokenKind kind;
    Token *next;
    int val;
    char *str;
    int len;
};

typedef enum
{
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_NUM,
} NodeKind;

typedef struct Node Node;

struct Node
{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val; // kindがND_NUMの場合のみ使う
};

Node *new_node(NodeKind kind, Node *lhs, Node *rhs)
{
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val)
{
    Node *node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

Token *token;
char *user_input;

void error(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char *loc, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

bool consume(char *op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len))
    {
        return false;
    }
    token = token->next;
    return true;
}

void expect(char *op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len))
    {
        error_at(token->str, "'%s'ではありません", op);
    }
    token = token->next;
}

int expect_number()
{
    if (token->kind != TK_NUM)
    {
        error_at(token->str, "数ではありません");
    }
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof()
{
    return token->kind == TK_EOF;
}

//lenはTK_RESERVED(記号)のときに使い、記号の文字長を表す。それ以外のときは-1を入れておく
Token *new_token(TokenKind kind, Token *cur, char *str, int len)
{
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    tok->len = len;
    cur->next = tok;
    return tok;
}
Token *tokenize(char *p)
{
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p)
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }
        if (memcmp(p, "==", 2) == 0)
        {
            cur = new_token(TK_RESERVED, cur, p, 2);
            p += 2;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')')
        {
            cur = new_token(TK_RESERVED, cur, p++, 1);

            continue;
        }
        if (isdigit(*p))
        {
            cur = new_token(TK_NUM, cur, p, -1);
            cur->val = strtol(p, &p, 10);
            continue;
        }
        error_at(token->str, "トークナイズできません");
    }
    new_token(TK_EOF, cur, p, -1);
    return head.next;
}

Node *expr();
Node *mul();
Node *unary();
Node *term();

Node *expr()
{
    Node *node = mul();
    for (;;)
    {
        if (consume("+"))
        {
            node = new_node(ND_ADD, node, mul());
        }
        else if (consume("-"))
        {
            node = new_node(ND_SUB, node, mul());
        }
        else
        {
            return node;
        }
    }
}

Node *mul()
{

    Node *node = unary();
    for (;;)
    {
        if (consume("*"))
        {
            node = new_node(ND_MUL, node, unary());
        }
        else if (consume("/"))
        {
            node = new_node(ND_DIV, node, unary());
        }
        else
        {
            return node;
        }
    }
}

Node *unary()
{
    if (consume("+"))
    {
        return term();
    }
    if (consume("-"))
    {
        return new_node(ND_SUB, new_node_num(0), term());
    }
    return term();
}

Node *term()
{
    if (consume("("))
    {
        Node *node = expr();
        expect(")");
        return node;
    }
    return new_node_num(expect_number());
}

void gen(Node *node)
{

    if (node->kind == ND_NUM)
    {
        printf(" push %d\n", node->val);
        return;
    }
    gen(node->lhs);
    gen(node->rhs);
    printf(" pop rdi\n");
    printf(" pop rax\n");

    switch (node->kind)
    {
    case ND_ADD:
        printf(" add rax, rdi\n");
        break;
    case ND_SUB:
        printf(" sub rax, rdi\n");
        break;
    case ND_MUL:
        printf(" imul rax, rdi\n");
        break;
    case ND_DIV:
        printf(" cqo\n");
        printf(" idiv rdi\n");
        break;
    }
    printf(" push rax\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません\n");
        exit(1);
    }
    user_input = argv[1];
    token = tokenize(argv[1]);

    Node *node = expr();

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    gen(node);

    printf(" pop rax\n");
    printf(" ret\n");
    return 0;
}