#include "9cc.h"
Token *token;
char *user_input;
Node *code[1024];

Node *new_node(NodeKind kind, Node *lhs, Node *rhs)
{
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val)
{
    Node *node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

void error(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char *loc, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

bool consume(char *op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len))
    {
        return false;
    }
    token = token->next;
    return true;
}

bool consume_tokenkind(TokenKind kind)
{
    if (token->kind != kind)
    {
        return false;
    }
    token = token->next;
    return true;
}

Token *consume_ident()
{
    if (token->kind != TK_IDENT)
    {
        return NULL;
    }
    Token *tok = token;
    token = token->next;
    return tok;
}

void expect(char *op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len))
    {
        error_at(token->str, "'%s'ではありません", op);
    }
    token = token->next;
}

int expect_number()
{
    if (token->kind != TK_NUM)
    {
        error_at(token->str, "数ではありません");
    }
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof()
{
    return token->kind == TK_EOF;
}
Token *next_token()
{
    if (at_eof())
    {
        error("プログラムの終端でnext_token()が呼ばれました\n");
    }
    return token->next;
}

//現在のトークンのstrがopで指定したものか調べる関数
bool check_token(char *op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len))
    {
        return false;
    }
    return true;
}

bool is_alnum(char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           (c == '_');
}

//lenはTK_RESERVED(記号)のときに使い、記号の文字長を表す。それ以外のときは-1を入れておく
Token *new_token(TokenKind kind, Token *cur, char *str, int len)
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
        //fprintf(stderr, "%c\n", *p);
        if (isspace(*p))
        {
            p++;
            continue;
        }
        if ((memcmp(p, "==", 2) == 0) || (memcmp(p, "!=", 2) == 0) || (memcmp(p, "<=", 2) == 0) || (memcmp(p, ">=", 2) == 0))
        {
            cur = new_token(TK_RESERVED, cur, p, 2);
            p += 2;
            continue;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%' || *p == '(' || *p == ')' || *p == '<' || *p == '>' || *p == '=' || *p == ';' || *p == '{' || *p == '}')
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
        else if ((strncmp(p, "return", 6) == 0) && !is_alnum(p[6]))
        {
            cur = new_token(TK_RETURN, cur, p, 6);
            p += 6;
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

void program()
{
    int i = 0;
    while (!at_eof())
    {
        code[i++] = stmt();
    }
    code[i] = NULL;
}

Node *stmt()
{

    Node *node;
    if (consume_tokenkind(TK_RETURN))
    {
        //fprintf(stderr, "%s\n", token->str);

        node = calloc(1, sizeof(Node));
        node->kind = ND_RETURN;
        node->lhs = expr();
        //fprintf(stderr, "%s\n", token->str);
        expect(";");
        return node;
    }
    else if (consume_tokenkind(TK_IF))
    {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_IF;
        node->lhs = expr();
        expect(")");
        Node *node_stmt_true = stmt();
        if (consume_tokenkind(TK_ELSE))
        {
            node->kind = ND_IFELSE;
            node->rhs = new_node(ND_IFELSE, node_stmt_true, stmt());
        }
        else
        {
            node->rhs = node_stmt_true;
        }
        return node;
    }
    else if (consume_tokenkind(TK_WHILE))
    {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_WHILE;
        node->lhs = expr();
        expect(")");
        node->rhs = stmt();
        return node;
    }
    else if (consume_tokenkind(TK_FOR))
    {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_FOR;

        //for (A;B;C) D; のA,Bを格納するノード
        Node *node_init_cond = calloc(1, sizeof(Node));

        //for (A;B;C) D; のC,Dを格納するノード
        Node *node_update_stmt = calloc(1, sizeof(Node));
        if (!check_token(";"))
        {
            node_init_cond->lhs = expr();
        }
        else
        {

            node_init_cond->lhs = NULL;
        }
        consume(";");

        if (!check_token(";"))
        {
            node_init_cond->rhs = expr();
        }
        else
        {
            node_init_cond->rhs = NULL;
        }
        consume(";");

        if (!check_token(")"))
        {
            node_update_stmt->lhs = expr();
        }
        else
        {
            node_update_stmt->lhs = NULL;
        }
        consume(";");

        expect(")");
        node_update_stmt->rhs = stmt();
        node->lhs = node_init_cond;
        node->rhs = node_update_stmt;
        return node;
    }
    else if (consume("{"))
    {
        node = calloc(1, sizeof(Node));
        node->kind = ND_BLOCK;
        node->block = calloc(1, sizeof(Block));

        Block *current_block = node->block;
        if (!(consume("}")))
        {
            for (;;)
            {
                current_block->stmt_node = stmt();
                if (consume("}"))
                    break;
                current_block = new_block(current_block);
            }
            current_block->next = NULL;
        }
        else
        {
            node->block = NULL;
        }
        return node;
    }
    else
    {
        node = expr();
        expect(";");
        return node;
    }
    error("stmtで解釈できません:%s\n", token->str);
}

Node *expr()
{
    return assign();
}

Node *assign()
{
    Node *node = equality();
    if (consume("="))
    {
        node = new_node(ND_ASSIGN, node, assign());
    }
    return node;
}

Node *equality()
{
    Node *node = relational();
    for (;;)
    {
        if (consume("=="))
        {

            node = new_node(ND_EQ, node, relational());
        }
        else if (consume("!="))
        {
            node = new_node(ND_NEQ, node, relational());
        }
        else
        {
            return node;
        }
    }
}

Node *relational()
{
    Node *node = add();
    for (;;)
    {
        if (consume("<="))
        {
            node = new_node(ND_LEQ, node, add());
        }
        else if (consume(">="))
        {
            node = new_node(ND_LEQ, add(), node);
        }
        else if (consume("<"))
        {
            node = new_node(ND_LT, node, add());
        }
        else if (consume(">"))
        {
            node = new_node(ND_LT, add(), node);
        }
        else
        {
            return node;
        }
    }
}

Node *add()
{
    Node *node = mul();
    for (;;)
    {
        if (consume("+"))
        {
            node = new_node(ND_ADD, node, mul());
        }
        else if (consume("-"))
        {
            node = new_node(ND_SUB, node, mul());
        }
        else
        {
            return node;
        }
    }
}

Node *mul()
{

    Node *node = unary();
    for (;;)
    {
        if (consume("*"))
        {
            node = new_node(ND_MUL, node, unary());
        }
        else if (consume("/"))
        {
            node = new_node(ND_DIV, node, unary());
        }
        else if (consume("%"))
        {
            node = new_node(ND_MOD, node, unary());
        }
        else
        {
            return node;
        }
    }
}

Node *unary()
{
    if (consume("+"))
    {
        return term();
    }
    if (consume("-"))
    {
        return new_node(ND_SUB, new_node_num(0), term());
    }
    return term();
}

Node *term()
{
    if (consume("("))
    {
        Node *node = expr();
        expect(")");
        return node;
    }
    Token *tok = consume_ident();
    if (tok)
    {
        if (consume("("))
        {
            Node *node = calloc(1, sizeof(Node));
            node->kind = ND_FUNC;
            node->funcname = tok->str;
            node->funcnamelen = tok->len;
            expect(")");

            return node;
        }
        else
        {
            Node *node = calloc(1, sizeof(Node));
            node->kind = ND_LVAR;

            LVar *lvar = find_lvar(tok);
            if (lvar)
            {
                node->offset = lvar->offset;
            }
            else
            {

                lvar = calloc(1, sizeof(LVar));
                lvar->next = locals;
                lvar->name = tok->str;
                lvar->len = tok->len;
                lvar->offset = locals->offset + 8;
                node->offset = lvar->offset;
                locals = lvar;
            }
            return node;
        }
    }
    return new_node_num(expect_number());
}
