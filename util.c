#include "9cc.h"
void node_name(NodeKind kind, char *s)
{
    switch (kind)
    {
    case ND_ADD:
        strcpy(s, "ADD");
        break;
    case ND_ADDR:
        strcpy(s, "ADDR");
        break;
    case ND_ASSIGN:
        strcpy(s, "ASSIGN");
        break;
    case ND_BLOCK:
        strcpy(s, "BLOCK");
        break;
    case ND_CALL:
        strcpy(s, "CALL");
        break;
    case ND_DEREF:
        strcpy(s, "DEREF");
        break;
    case ND_DIV:
        strcpy(s, "DIV");
        break;
    case ND_EQ:
        strcpy(s, "EQ");
        break;
    case ND_FOR:
        strcpy(s, "FOR");
        break;
    case ND_FUNC:
        strcpy(s, "FUNC");
        break;
    case ND_IF:
        strcpy(s, "IF");
        break;
    case ND_IFELSE:
        strcpy(s, "IFELSE");
        break;
    case ND_LEQ:
        strcpy(s, "LEQ");
        break;
    case ND_LT:
        strcpy(s, "LT");
        break;
    case ND_LVAR:
        strcpy(s, "LVAR");
        break;
    case ND_MOD:
        strcpy(s, "MOD");
        break;
    case ND_MUL:
        strcpy(s, "MUL");
        break;
    case ND_NEQ:
        strcpy(s, "NEQ");
        break;
    case ND_NUM:
        strcpy(s, "NUM");
        break;
    case ND_RETURN:
        strcpy(s, "RETURN");
        break;
    case ND_SUB:
        strcpy(s, "SUB");
        break;
    case ND_WHILE:
        strcpy(s, "NEQ");
        break;
    }
}

void dumpAST(FILE *fp, Node *node)
{

    char *strparent = (char *)calloc(128, sizeof(char));
    char *strchild = (char *)calloc(128, sizeof(char));
    node_name(node->kind, strparent);
    if (node->kind == ND_BLOCK)
    {
        Block *cur = node->block;
        while (cur != NULL)
        {
            node_name(cur->stmt_node->kind, strchild);
            fprintf(fp, "\"%s@%p\" -> \"%s@%p\";\n", strparent, node, strchild, cur->stmt_node);
            dumpAST(fp, cur->stmt_node);
            cur = cur->next;
        }
    }
    else
    {
        if (node->lhs != NULL)
        {
            node_name(node->lhs->kind, strchild);
            fprintf(fp, "\"%s@%p\" -> \"%s@%p\";\n", strparent, node, strchild, node->lhs);
            dumpAST(fp, node->lhs);
        }

        if (node->rhs != NULL)
        {
            node_name(node->rhs->kind, strchild);
            fprintf(fp, "\"%s@%p\" -> \"%s@%p\";\n", strparent, node, strchild, node->rhs);
            dumpAST(fp, node->rhs);
        }
    }
}