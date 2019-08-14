#ifndef __9CC_H__
#define __9CC_H__
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
    ND_EQ,
    ND_NEQ,
    ND_LT,
    ND_LEQ
} NodeKind;

typedef struct Node Node;

struct Node
{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val; // kindがND_NUMの場合のみ使う
};
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *term();
void gen(Node *node);
Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Token *tokenize(char *p);
Node *expr();
extern Token *token;
extern char *user_input;

#endif