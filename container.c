#include "9cc.h"
LVar *locals;
LVar *find_lvar(Token *tok)
{
    LVar *var = locals;
    for (; var != NULL; var = var->next)
    {
        if (var->len == tok->len && !memcmp(tok->str, var->name, var->len))
        {
            return var;
        }
    }
    return NULL;
}

Block *new_block(Block *cur)
{
    Block *new_block = calloc(1, sizeof(Block));
    cur->next = new_block;
    return new_block;
}

Block *next_block(Block *block)
{
    return block->next;
}