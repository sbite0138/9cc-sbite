#include "9cc.h"
#include <errno.h>

void error(char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char* loc, char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char* line = loc;
    while (user_input < line && line[-1] != '\n') //負のインデックスはUB？
    {
        line--;
    }
    char* end = loc;
    while (*end != '\n')
        end++;
    int pos = loc - line;
    fprintf(stderr, "%.*s\n", (int)(end - line), line);
    fprintf(stderr, "%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    assert(false);
    exit(1);
}
void node_name(NodeKind kind, char* s)
{
    switch (kind) {
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
    case ND_GVAR:
        strcpy(s, "GVAR");
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
    case ND_NOP:
        strcpy(s, "NOP");
        break;
    }
}

void dumpAST(FILE* fp, Node* node)
{

    char* strparent = (char*)calloc(128, sizeof(char));
    char* strchild = (char*)calloc(128, sizeof(char));
    node_name(node->kind, strparent);
    if (node->kind == ND_BLOCK) {
        Block* cur = node->block;
        while (cur != NULL) {
            node_name(cur->stmt_node->kind, strchild);
            dumpAST(fp, cur->stmt_node);
            cur = cur->next;
        }
    } else {
        if (node->lhs != NULL) {
            node_name(node->lhs->kind, strchild);
            fprintf(fp, "\"%s@%p\" -> \"%s@%p\";\n", strparent, node, strchild, node->lhs);
            dumpAST(fp, node->lhs);
        }

        if (node->rhs != NULL) {
            node_name(node->rhs->kind, strchild);
            fprintf(fp, "\"%s@%p\" -> \"%s@%p\";\n", strparent, node, strchild, node->rhs);
            dumpAST(fp, node->rhs);
        }
    }
}

int get_array_offset(Type* type)
{
    if (type->ty != ARRAY) {
        error("call get_array_offset with non ARRAY type\n");
    }
    int offset = 1;
    Type* cur = type;
    while (cur->ty == ARRAY) {
        offset *= cur->array_size;
        cur = cur->base;
    }
    return offset;
}

char* read_file(char* path)
{
    FILE* fp = fopen(path, "r");
    if (!fp)
        error("cannot open %s: %s", path, strerror(errno));
    if (fseek(fp, 0, SEEK_END) == -1)
        error("%s: fseek: %s", path, strerror(errno));
    size_t size = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) == -1)
        error("%s: fseek: %s", path, strerror(errno));
    char* buf = calloc(1, size + 2);
    fread(buf, size, 1, fp);
    if (size == 0 || buf[size - 1] != '\n')
        buf[size++] = '\n';
    buf[size] = '\0';
    fclose(fp);
    return buf;
}

int type_size(Type* type)
{
    if (type->ty == CHAR) {
        return 1;
    }
    if (type->ty == INT) {
        return 4;
    }
    if (type->ty == PTR) {
        return 8;
    }
    if (type->ty == ARRAY) {
        return type->array_size * type_size(type->base);
    }
    if (type->ty == STRUCT) {
        int ret = 0;
        Member* cur = type->members;
        while (cur != NULL) {
            ret += type_size(cur->ty);
            cur = cur->next;
        }
        return ret;
    }

    error("不明なタイプです:%d", type->ty);
}

int get_array_dimesion(Type* type)
{
    int ret = 0;
    Type* cur = type;
    while (cur->ty == ARRAY) {
        ret++;
        cur = cur->base;
    }
    return ret;
}