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
    case ND_NUM:
        node->type2->ty = INT;
        break;
    case ND_ADD:
    case ND_SUB:
    case ND_MUL:
    case ND_DIV:
        break;
    }
}