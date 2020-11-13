#include "9cc.h"

Variable* locals;
Variable* globals;
Tag* tags;
Str* strings;

Variable* find_variable(Token* tok, Variable* root)
{
    Variable* var = root;
    for (; var != NULL; var = var->next) {
        if (var->len == tok->len && !memcmp(tok->str, var->name, var->len)) {
            return var;
        }
    }
    return NULL;
}
Tag* find_tag(Token* tok)
{
    Tag* tag = tags;
    for (; tag != NULL; tag = tag->next) {
        if (tag->len == tok->len && !memcmp(tok->str, tag->name, tag->len)) {
            return tag;
        }
    }
    return NULL;
}

Member*
find_member(Member* head, char* name)
{
    Member* cur = head;
    while (cur != NULL) {
        // fprintf(stderr, "%c %s %d\n", cur->name[0], name, cur->len);
        if (strncmp(cur->name, name, cur->len) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Block* new_block()
{
    Block* new = calloc(1, sizeof(Block));
    return new;
}

Block* next_block(Block* cur)
{
    return cur->next;
}

Arg* new_arg(Arg* cur)
{
    Arg* new = calloc(1, sizeof(Arg));
    cur->next = new;
    return new;
}

Arg* next_arg(Arg* cur)
{
    return cur->next;
}

Str* find_str(char* s, int len)
{
    Str* cur = strings;
    for (; cur != NULL; cur = cur->next) {
        if (strncmp(cur->str, s, len) == 0) {
            return cur;
        }
    }
    return NULL;
}
