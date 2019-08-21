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
    TK_IDENT,
    TK_NUM,
    TK_IF,
    TK_ELSE,
    TK_WHILE,
    TK_RETURN,
    TK_FOR,
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
    ND_MOD,
    ND_NUM,
    ND_EQ,
    ND_NEQ,
    ND_LT,
    ND_LEQ,
    ND_ASSIGN,
    ND_LVAR,
    ND_CALL,
    ND_IF,
    ND_IFELSE,
    ND_WHILE,
    ND_FOR,
    ND_BLOCK,
    ND_RETURN
} NodeKind;

typedef struct Node Node;
typedef struct Block Block;
typedef struct LVar LVar;
typedef struct Arg Arg;

struct Node
{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    Block *block;
    int val;         // kindがND_NUMの場合のみ使う
    int offset;      // kindがND_LVARの場合のみ使う
    char *funcname;  //kindがND_CALLの場合のみ使う
    int funcnamelen; //kindがND_CALLの場合のみ使う
    Arg *args;       //kindがND_CALLの場合のみ使う
};
struct Block
{
    Node *stmt_node;
    Block *next;
};

struct LVar
{
    LVar *next;
    char *name;
    int len;
    int offset;
};
struct Arg
{
    Node *node;
    Arg *next;
};

void error(char *fmt, ...);

void program();
Node *stmt();
Node *expr();
Node *assign();
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

LVar *find_lvar(Token *tok);
Block *new_block(Block *cur);
Block *next_block(Block *block);
Arg *new_arg(Arg *cur);
Arg *next_arg(Arg *cur);

extern Token *token;
extern char *user_input;
extern Node *code[1024];
extern LVar *locals;
extern int label;
extern char **arg_reg;
#endif