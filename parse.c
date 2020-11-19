#include "9cc.h"

Token* token;
char* user_input;
Node* code[1024];
Variable* func_variables[256];

Node* new_node_num(int val)
{
    Node* node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    node->type = calloc(1, sizeof(Type));
    node->type2 = calloc(1, sizeof(Type));
    node->type->ty = INT; // calloc(1, sizeof(Type));
    node->type2 = node->type;
    return node;
}

Node* new_node(NodeKind kind, Node* lhs, Node* rhs)
{
    Node* node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    node->type = calloc(1, sizeof(Type));
    node->type2 = calloc(1, sizeof(Type));

    // fprintf(stderr, "%d %d\n", lhs->type->ty, rhs->type->ty);
    // fprintf(stderr, "%s\n", token->str);
    if (node->kind == ND_ADD) {
        //  fprintf(stderr, "%d %d\n", lhs->kind, rhs->kind);
        // print_type(node->lhs->type);
        if (lhs->type->ty == PTR && rhs->type->ty == PTR) {
            error("ポインタ同士の加算です:%s", token->str);
        } else if (is_numeric(lhs->type) && is_numeric(rhs->type)) {
            node->type->ty = INT;
        } else if ((lhs->type->ty == ARRAY && is_numeric(rhs->type)) || (is_numeric(lhs->type) && rhs->type->ty == ARRAY)) {
            node->type->ty = PTR;
            assert(is_numeric(lhs->type) + is_numeric(rhs->type) == 1);
            if (!is_numeric(lhs->type)) {
                node->type->base = lhs->type->base;
            } else {
                node->type->base = rhs->type->base;
            }
        } else {
            node->type->ty = PTR;
            assert(is_numeric(lhs->type) + is_numeric(rhs->type) == 1);
            if (!is_numeric(lhs->type)) {
                node->rhs = new_node(ND_MUL, rhs, new_node_num(type_size(lhs->type->base)));
                node->type->base = lhs->type->base;
            } else {
                node->lhs = new_node(ND_MUL, lhs, new_node_num(type_size(rhs->type->base)));
                node->type->base = rhs->type->base;
            }
        }
    } else if (node->kind == ND_SUB) {
        //  fprintf(stderr, "%d %d\n", lhs->kind, rhs->kind);
        // print_type(node->lhs->type);
        if (is_numeric(lhs->type) && is_numeric(rhs->type)) {
            //lhs,rhsともに数値
            node->type->ty = INT;
        } else if (!is_numeric(lhs->type) && !is_numeric(rhs->type)) {
            //lhs,rhsともにポインタ
            node->type->ty = INT;
        } else if ((lhs->type->ty == ARRAY && is_numeric(rhs->type)) || (is_numeric(lhs->type) && rhs->type->ty == ARRAY)) {
            node->type->ty = PTR;
            assert(is_numeric(lhs->type) + is_numeric(rhs->type) == 1);
            if (!is_numeric(lhs->type)) {
                node->type->base = lhs->type->base;
            } else {
                node->type->base = rhs->type->base;
            }
        } else {
            node->type->ty = PTR;
            assert(is_numeric(lhs->type) + is_numeric(rhs->type) == 1);
            if (!is_numeric(lhs->type)) {
                node->rhs = new_node(ND_MUL, rhs, new_node_num(type_size(lhs->type->base)));
                node->type->base = lhs->type->base;
            } else {
                node->lhs = new_node(ND_MUL, lhs, new_node_num(type_size(rhs->type->base)));
                node->type->base = rhs->type->base;
            }
        }
    }
    node->type2 = node->type;
    return node;
}

void print_type(Type* type)
{
    switch (type->ty) {
    case INT:
        fprintf(stderr, "INT\n");
        return;
    case CHAR:
        fprintf(stderr, "CHAR\n");
        return;
    case PTR:
        fprintf(stderr, "PTR->");
        print_type(type->base);
        return;
    case ARRAY:
        fprintf(stderr, "ARRAY[%d]->", type->array_size);
        print_type(type->base);
        return;
    }
}

bool consume(char* op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) {
        return false;
    }
    token = token->next;
    return true;
}

bool consume_tokenkind(TokenKind kind)
{
    if (token->kind != kind) {
        return false;
    }
    token = token->next;
    return true;
}

Token* consume_ident()
{
    if (token->kind != TK_IDENT) {
        return NULL;
    }
    Token* tok = token;
    token = token->next;
    return tok;
}

void expect(char* op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) {
        error_at(token->str, "'%s'ではありません", op);
    }
    token = token->next;
}

int expect_number()
{
    if (token->kind != TK_NUM) {
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
void next_token()
{
    if (at_eof()) {
        error("プログラムの終端でnext_token()が呼ばれました\n");
    }
    token = token->next;
}

//現在のトークンのstrがopで指定したものか調べる関数
bool check_token(char* op)
{
    if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) {
        return false;
    }
    return true;
}

void program()
{
    int i = 0;
    globals = NULL;
    strings = NULL;
    while (!at_eof()) {
        locals = calloc(1, sizeof(Variable));
        locals->offset = 8;
        code[i] = toplevel();
        //トップレベルには関数かグローバル変数の定義が入る。
        //グローバル変数の場合、戻り値はNULLになる（宣言は新しいnodeを生成しないので）
        //返った結果がNULLかどうかで処理を分けている
        if (code[i] != NULL) {
            func_variables[i] = locals;
            i += 1;
        }
    }

    code[i] = NULL;
}

Type* decl_type()
{
    int base_type = token->kind;
    next_token();
    Type* type = calloc(1, sizeof(Type));

    if (base_type == TK_STRUCT) {
        type->ty = STRUCT;
        if (consume("{")) {
            //無名構造体
            type->members = calloc(1, sizeof(Member));
            Member* cur = type->members;
            int offset = 0;
            while (true) {

                cur->ty = decl_type();
                cur->name = token->str;
                cur->len = token->len;
                cur->offset = offset;
                offset += type_size(cur->ty);
                next_token();
                consume(";");
                if (consume("}"))
                    break;
                Member* next = calloc(1, sizeof(Member));
                cur->next = next;
                cur = next;
            }
        }
        return type;
    } else {

        Type* cur = type;
        while (consume("*")) {
            cur->ty = PTR;
            Type* next = calloc(1, sizeof(Type));
            cur->base = next;
            cur = next;
        }
        switch (base_type) {
        case TK_INT:
            cur->ty = INT;
            break;
        case TK_CHAR:
            cur->ty = CHAR;
            break;
        }
        return type;
    }
}
void decl_lvar()
{
    Variable* lvar = calloc(1, sizeof(Variable));

    Type* base = decl_type();
    if (consume(";")) {
        return;
    }
    Type* head = NULL;
    Type* cur = NULL;
    lvar->next = locals;
    lvar->name = token->str;
    lvar->type = calloc(1, sizeof(Type));
    lvar->len = token->len;
    next_token();

    int size = 1;
    while (consume("[")) {
        // head->...->cur->base #=> head->...->cur->node->base にする
        Type* node = calloc(1, sizeof(Type));

        node->ty = ARRAY;
        node->array_size = token->val;

        node->base = base;
        if (head == NULL) {
            head = node;
            cur = node;
        } else {
            cur->base = node;
            cur = node;
        }
        size *= token->val;
        next_token();
        expect("]");
    }
    if (head == NULL) {
        lvar->type = base;
    } else {
        lvar->type = head;
    }

    if (lvar->type->ty == INT) {
        lvar->offset = locals->offset + 4 * size;
    } else if (lvar->type->ty == CHAR) {
        lvar->offset = locals->offset + size;
    } else {
        lvar->offset = locals->offset + 8 * size;
    }
    // node->offset = lvar->offset;

    locals = lvar;
    expect(";");
}
Node* toplevel()
{
    Type* type = decl_type();

    Node* node = calloc(1, sizeof(Node));
    char* name = token->str;
    int len = token->len;
    next_token();

    if (consume("(")) {
        node->kind = ND_FUNC;
        node->funcname = name;
        node->funcnamelen = len;
        node->argnum = 0;
        Node* cur = node;
        if (!consume(")")) {
            for (;;) {
                Variable* lvar = calloc(1, sizeof(Variable));
                lvar->type = decl_type();
                // print_type(lvar->type);
                lvar->next = locals;
                lvar->name = token->str;
                lvar->len = token->len;
                lvar->offset = locals->offset + type_size(lvar->type);
                locals = lvar;
                node->argnum += 1;
                next_token();

                if (!consume(",")) {
                    break;
                }
            }
            expect(")");
        }
        //今のままだとint foo() return 42;みたいなコードのコンパイルが通る
        node->rhs = stmt();
        return node;
    } else {
        Variable* lvar = calloc(1, sizeof(Variable));
        lvar->type = type;
        lvar->next = globals;
        lvar->name = name;
        lvar->len = len;
        int size = 1;
        while (consume("[")) {
            Type* next = calloc(1, sizeof(Type));
            next->ty = ARRAY;
            next->base = lvar->type;
            lvar->type = next;
            size *= token->val;
            next->array_size = token->val;
            next_token();
            expect("]");
        }
        if (lvar->type->ty == INT) {
            lvar->size = 4 * size;
        }
        if (lvar->type->ty == CHAR) {
            lvar->size = 1 * size;
        } else {
            // TODO: 他の型(structとか)も扱えるようにする
            lvar->size = 8 * size;
        }
        globals = lvar;
        expect(";");
        return NULL;
    }
}

Node* stmt()
{
    Node* node;
    if (consume_tokenkind(TK_RETURN)) {
        node = calloc(1, sizeof(Node));
        node->kind = ND_RETURN;
        node->lhs = expr();
        expect(";");
        return node;
    } else if (consume_tokenkind(TK_IF)) {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_IF;
        node->lhs = expr();
        expect(")");
        Node* node_stmt_true = stmt();
        if (consume_tokenkind(TK_ELSE)) {
            node->kind = ND_IFELSE;
            node->rhs = new_node(ND_IFELSE, node_stmt_true, stmt());
        } else {
            node->rhs = node_stmt_true;
        }
        return node;
    } else if (consume_tokenkind(TK_WHILE)) {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_WHILE;
        node->lhs = expr();
        expect(")");
        node->rhs = stmt();
        return node;
    } else if (consume_tokenkind(TK_FOR)) {
        expect("(");
        node = calloc(1, sizeof(Node));
        node->kind = ND_FOR;

        // for (A;B;C) D; のA,Bを格納するノード
        Node* node_init_cond = calloc(1, sizeof(Node));

        // for (A;B;C) D; のC,Dを格納するノード
        Node* node_update_stmt = calloc(1, sizeof(Node));
        if (!check_token(";")) {
            node_init_cond->lhs = expr();
        } else {
            node_init_cond->lhs = NULL;
        }
        consume(";");

        if (!check_token(";")) {
            node_init_cond->rhs = expr();
        } else {
            node_init_cond->rhs = NULL;
        }
        consume(";");

        if (!check_token(")")) {
            node_update_stmt->lhs = expr();
        } else {
            node_update_stmt->lhs = NULL;
        }
        consume(";");

        expect(")");
        node_update_stmt->rhs = stmt();
        node->lhs = node_init_cond;
        node->rhs = node_update_stmt;
        return node;
    } else if (consume("{")) {
        /*
BLOCK=
"{" (declvar* stmt declvar*)* "}" |
"{" (declvar*) "}"
という構文になる
*/
        node = calloc(1, sizeof(Node));
        node->kind = ND_BLOCK;
        node->block = calloc(1, sizeof(Block));

        Block* current_block = node->block;
        // while (!consume("}"))とすることで，{}みたいな空のブロックにも対応できる
        while (!consume("}")) {

            //fprintf(stderr, "a %s", token->str);
            if (token->kind == TK_INT || token->kind == TK_CHAR || token->kind == TK_STRUCT) {
                decl_lvar();
            } else {
                current_block->stmt_node = stmt();
                //fprintf(stderr, "b %s", token->str);
                if (consume("}"))
                    break;
                current_block->next = new_block(current_block);
                current_block = current_block->next;
            }
            //fprintf(stderr, "c %s", token->str);
        }
        current_block->next = NULL;
        return node;
    } else {
        node = expr();
        expect(";");
        return node;
    }
    // never reachable!!!
    error("stmtで解釈できません:%s\n", token->str);
}

Node* expr()
{
    return assign();
}

Node* assign()
{
    Node* node = equality();
    if (consume("=")) {
        node = new_node(ND_ASSIGN, node, assign());
    }
    return node;
}

Node* equality()
{
    Node* node = relational();
    for (;;) {
        if (consume("==")) {
            node = new_node(ND_EQ, node, relational());
        } else if (consume("!=")) {
            node = new_node(ND_NEQ, node, relational());
        } else {
            return node;
        }
    }
}

Node* relational()
{
    Node* node = add();
    for (;;) {
        if (consume("<=")) {
            node = new_node(ND_LEQ, node, add());
        } else if (consume(">=")) {
            node = new_node(ND_LEQ, add(), node);
        } else if (consume("<")) {
            node = new_node(ND_LT, node, add());
        } else if (consume(">")) {
            node = new_node(ND_LT, add(), node);
        } else {
            return node;
        }
    }
}

Node* add()
{
    Node* node = mul();
    for (;;) {
        if (consume("+")) {
            node = new_node(ND_ADD, node, mul());
        } else if (consume("-")) {
            node = new_node(ND_SUB, node, mul());
        } else {
            return node;
        }
    }
}

Node* mul()
{
    Node* node = unary();
    for (;;) {
        if (consume("*")) {
            node = new_node(ND_MUL, node, unary());
        } else if (consume("/")) {
            node = new_node(ND_DIV, node, unary());
        } else if (consume("%")) {
            node = new_node(ND_MOD, node, unary());
        } else {
            return node;
        }
    }
}

Node* unary()
{
    if (consume("+")) {
        return term();
    }
    if (consume("-")) {
        return new_node(ND_SUB, new_node_num(0), term());
    }
    if (consume("&")) {
        Node* node = calloc(1, sizeof(Node));
        node->kind = ND_ADDR;
        node->rhs = unary();
        node->type = calloc(1, sizeof(Type));
        node->type->ty = PTR;
        node->type->base = node->rhs->type;
        return node;
    }

    if (consume("*")) {
        Node* node = calloc(1, sizeof(Node));
        node->kind = ND_DEREF;
        node->rhs = unary();
        // node->type = calloc(1, sizeof(Type));
        node->type = node->rhs->type->base;
        return node;
    }
    if (consume_tokenkind(TK_SIZEOF)) {
        Node* node = unary();
        return new_node_num(type_size(node->type));
    }
    return term();
}

Node* term()
{
    if (consume("(")) {
        Node* node = expr();
        expect(")");
        return node;
    }
    Token* tok = consume_ident();
    if (tok) {
        if (consume("(")) {
            Node* node = calloc(1, sizeof(Node));
            node->args = calloc(1, sizeof(Arg));
            node->kind = ND_CALL;
            node->type = calloc(1, sizeof(Type));
            node->type->ty = INT;
            node->funcname = tok->str;
            node->funcnamelen = tok->len;
            node->argnum = 0;
            Arg* curarg = node->args;
            if (!check_token(")")) {
                for (;;) {
                    curarg->node = expr();
                    node->argnum++;
                    // curarg->node->kind = ND_NUM;
                    if (!consume(","))
                        break;
                    curarg = new_arg(curarg);
                }
                curarg->next = NULL;
            } else {
                node->args = NULL;
            }
            expect(")");
            return node;
        } else {
            int var_type;
            Node* node = calloc(1, sizeof(Node));
            node->kind = ND_LVAR;
            Variable* lvar = find_variable(tok, locals);
            var_type = ND_LVAR;
            if (lvar == NULL) {
                node->kind = ND_GVAR;
                var_type = ND_GVAR;
                lvar = find_variable(tok, globals);
            }
            if (lvar) {
                if (lvar->type->ty == ARRAY) {
                    // lvarが配列
                    if (consume("[")) {
                        // lvar[0]みたいな部分はDEREFをする場合とそうでない場合があって，
                        // lvarばN次元配列の時，lvar[][][]...[] (K個)の時，K!=NならDEREFは行わない

                        node->kind = var_type;
                        node->offset = lvar->offset;
                        node->type = calloc(1, sizeof(Type));
                        node->type->ty = ARRAY;
                        node->type->base = lvar->type->base;

                        if (var_type == ND_GVAR) {
                            node->gvarname = lvar->name;
                            node->gvarnamelen = lvar->len;
                        }

                        Type* cur = lvar->type;
                        do {
                            Node* index = add();
                            Node* mul = new_node(
                                ND_MUL, index, new_node_num(type_size(cur->base)));
                            cur = cur->base;
                            node = new_node(ND_ADD, node, mul);
                            Node* deref = calloc(1, sizeof(Node));
                            deref->kind = ND_DEREF;
                            deref->rhs = node;
                            deref->type = node->type->base;
                            node = deref;
                            expect("]");
                        } while (consume("["));
                        // node->type = calloc(1, sizeof(Type));

                        print_type(node->type);

                        // node->type = node->type->ptr_to;
                    } else {
                        node->kind = ND_ADDR;
                        Node* node_lvar = calloc(1, sizeof(Node));
                        node_lvar->kind = var_type;
                        node_lvar->offset = lvar->offset;
                        node_lvar->type = lvar->type;
                        if (var_type == ND_GVAR) {
                            node_lvar->gvarname = lvar->name;
                            node_lvar->gvarnamelen = lvar->len;
                        }
                        node->rhs = node_lvar;
                        node->type = calloc(1, sizeof(Type));
                        node->type->ty = PTR;
                        node->type->base = lvar->type->base;
                    }
                } else if (lvar->type->ty == STRUCT) {
                    if (consume(".")) {
                        Member* member = find_member(lvar->type->members, token->str);
                        node->offset = lvar->offset + member->offset;
                        node->type = member->ty;
                        // fprintf(stderr, "%p\n", member->ty);
                        next_token(token);
                    } else {
                        node->offset = lvar->offset;
                        node->type = lvar->type;
                        if (var_type == ND_GVAR) {
                            node->gvarname = lvar->name;
                            node->gvarnamelen = lvar->len;
                        }
                    }
                } else {
                    if (consume("[") && lvar->type->ty == PTR) {
                        node->kind = ND_DEREF;
                        Node* node_lvar = calloc(1, sizeof(Node));
                        node_lvar->kind = var_type;
                        node_lvar->offset = lvar->offset;
                        node_lvar->type = calloc(1, sizeof(Type));
                        node_lvar->type->ty = PTR;
                        node_lvar->type->base = lvar->type->base;
                        if (var_type == ND_GVAR) {
                            node_lvar->gvarname = lvar->name;
                            node_lvar->gvarnamelen = lvar->len;
                        }
                        Node* node_index = add();
                        node->rhs = new_node(ND_ADD, node_lvar, node_index);
                        node->type = node->rhs->type->base;
                        expect("]");
                    } else {
                        node->offset = lvar->offset;
                        node->type = lvar->type;
                        if (var_type == ND_GVAR) {
                            node->gvarname = lvar->name;
                            node->gvarnamelen = lvar->len;
                        }
                    }
                }
            } else {
                char* name = calloc(128, sizeof(char));
                strncpy(name, tok->str, tok->len);
                error("定義されていない変数名です:%s\n", name);
            }
            return node;
        }
    }
    if (token->kind == TK_STR) {
        Node* node = calloc(1, sizeof(Node));
        node->kind = ND_STR;
        Str* str = calloc(1, sizeof(Str));
        str->str = token->str;
        str->len = token->len;
        if (strings == NULL) {
            str->id = 0;
        } else {
            str->id = strings->id + 1;
        }
        str->next = strings;
        strings = str;
        node->str = str;

        next_token();
        return node;
    }
    return new_node_num(expect_number());
}
