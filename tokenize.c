#include "9cc.h"
bool is_alnum(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || (c == '_');
}

// lenはTK_RESERVED(記号)のときに使い、記号の文字長を表す。それ以外のときは-1を入れておく
Token *
new_token(TokenKind kind, Token *cur, char *str, int len)
{
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    tok->len = len;
    cur->next = tok;
    return tok;
}
Token *tokenize(char *p)
{
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p)
    {
        // fprintf(stderr, "%c\n", *p);
        if (isspace(*p) || *p == '\n')
        {
            p++;
            continue;
        }
        else if (strncmp(p, "//", 2) == 0)
        {
            p += 2;
            while (*p != '\n')
            {
                p++;
            }
            p++;
            continue;
        }
        else if ((memcmp(p, "==", 2) == 0) || (memcmp(p, "!=", 2) == 0) || (memcmp(p, "<=", 2) == 0) || (memcmp(p, ">=", 2) == 0) || (memcmp(p, "->", 2) == 0))
        {
            cur = new_token(TK_RESERVED, cur, p, 2);
            p += 2;
            continue;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%' || *p == '.' || *p == '(' || *p == ')' || *p == '<' || *p == '>' || *p == '=' || *p == ';' || *p == '{' || *p == '}' || *p == ',' || *p == '&' || *p == '[' || *p == ']')
        {
            cur = new_token(TK_RESERVED, cur, p++, 1);
            continue;
        }
        else if ((strncmp(p, "if", 2) == 0) && !is_alnum(p[2]))
        {
            cur = new_token(TK_IF, cur, p, 2);
            p += 2;
            continue;
        }
        else if ((strncmp(p, "else", 4) == 0) && !is_alnum(p[4]))
        {
            cur = new_token(TK_ELSE, cur, p, 4);
            p += 4;
            continue;
        }
        else if ((strncmp(p, "while", 5) == 0) && !is_alnum(p[5]))
        {
            cur = new_token(TK_WHILE, cur, p, 5);
            p += 5;
            continue;
        }
        else if ((strncmp(p, "for", 3) == 0) && !is_alnum(p[3]))
        {
            cur = new_token(TK_FOR, cur, p, 3);
            p += 3;
            continue;
        }
        else if ((strncmp(p, "sizeof", 6) == 0) && !is_alnum(p[6]))
        {
            cur = new_token(TK_SIZEOF, cur, p, 6);
            p += 6;
            continue;
        }
        else if ((strncmp(p, "return", 6) == 0) && !is_alnum(p[6]))
        {
            cur = new_token(TK_RETURN, cur, p, 6);
            p += 6;
            continue;
        }
        else if ((strncmp(p, "struct", 6) == 0) && !is_alnum(p[6]))
        {
            cur = new_token(TK_STRUCT, cur, p, 6);
            p += 6;
            continue;
        }
        else if ((strncmp(p, "int", 3) == 0) && !is_alnum(p[3]))
        {
            cur = new_token(TK_INT, cur, p, 3);
            p += 3;
            continue;
        }
        else if ((strncmp(p, "char", 4) == 0) && !is_alnum(p[4]))
        {
            cur = new_token(TK_CHAR, cur, p, 4);
            p += 4;
            continue;
        }
        else if (*p == '\'')
        {
            cur = new_token(TK_NUM, cur, p, -1);
            p++;
            char c = *p;
            if (c != '\\')
            {
                p++;
            }
            else
            {
                p++;
                c = *p;
                if (c == 'n')
                {
                    c = '\n';
                }
                p++;
            }
            if (*p != '\'')
            {
                error("\'\'の間に複数文字が入っています");
            }
            p++;
            cur->val = (int)c;
            continue;
        }
        else if (*p == '\"')
        {
            int len = 1;
            // fprintf(stderr, "str\n");
            while (*(p + len) != '\"')
            {
                if (*(p + len) == '\\')
                {
                    len++;
                }
                len++;
            }
            len++;
            cur = new_token(TK_STR, cur, p, len);
            p += len;
            // fprintf(stderr, "%s\n", p);
            continue;
        }
        else if (isalpha(*p))
        {
            int len = 0;
            // is_alnumは自作した関数で、標準で用意されているisalnumではない(前者は引数が'_'の場合もtrueを返す)
            while (is_alnum(*(p + len)))
            {
                len++;
            }
            cur = new_token(TK_IDENT, cur, p, len);
            p += len;
            continue;
        }
        else if (isdigit(*p))
        {
            cur = new_token(TK_NUM, cur, p, -1);
            cur->val = strtol(p, &p, 10);
            continue;
        }
        error_at(token->str, "トークナイズできません");
    }
    new_token(TK_EOF, cur, p, -1);
    return head.next;
}