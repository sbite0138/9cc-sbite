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