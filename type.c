#include "9cc.h"

int is_numeric(Type* type)
{
    return type->ty == INT || type->ty == CHAR;
}

void add_type(Node* node)
{

    if (node == NULL || node->type2) {
        return;
    }
    add_type(node->rhs);
    add_type(node->lhs);
    for (Block* cur = node->block; cur != NULL; cur = cur->next) {
        add_type(cur->stmt_node);
    }
    for (Arg* cur = node->args; cur != NULL; cur = cur->next) {
        add_type(cur->node);
    }
    node->type2 = calloc(1, sizeof(Type));

    switch (node->kind) {
    case ND_ADD:
    case ND_SUB:
        error("すでに型がつけられているはず");
        break;
    case ND_MUL:
    case ND_DIV:
    case ND_MOD:
    case ND_NUM:
    case ND_EQ:
    case ND_NEQ:
    case ND_LT:
    case ND_LEQ:
    case ND_ASSIGN:
    case ND_ADDR:
    case ND_DEREF:
    case ND_LVAR:
    case ND_FUNC:
    case ND_GVAR:
    case ND_STR:
    case ND_CALL:
    case ND_IF:
    case ND_IFELSE:
    case ND_WHILE:
    case ND_FOR:
    case ND_BLOCK:
    case ND_RETURN:
    case ND_NOP:
        break;
    }
}