#include "9cc.h"

void add_type(Node* node)
{
    if (node == NULL || node->type->ty) {
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
    node->type = calloc(1, sizeof(Type));

    switch (node->kind) {
    case ND_NUM:
        node->type->ty = INT;
        break;
    case ND_ADD:
    case ND_SUB:
    case ND_MUL:
    case ND_DIV:
        node->type->ty = INT;
        break;
    }
}