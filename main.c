#include "ATLAS.h"

void print_node(Node *node) {
    if (!node) return;

    print_node(node->lhs);

    switch (node->kind) {
        case ND_ADD:
            printf(" + ");
            break;
        case ND_SUB:
            printf(" - ");
            break;
        case ND_MUL:
            printf(" * ");
            break;
        case ND_DIV:
            printf(" / ");
            break;
        case ND_ASSIGN:
            printf(" = ");
            break;
        case ND_EQ:
            printf(" == ");
            break;
        case ND_NE:
            printf(" != ");
            break;
        case ND_LT:
            printf(" < ");
            break;
        case ND_LE:
            printf(" <= ");
            break;
        case ND_LVAL:
            printf(" %s ", node->name);
            break;
        case ND_NUM:
            printf(" %ld ", node->val);
            break;
    }

    print_node(node->rhs);
}

void print_program(Node *node) {
    for (Node *n = node; n; n = n->next) {
        print_node(n);
        printf(";\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        error("引数の数が間違っています。");

    // 入力をuser_inputに保存する
    user_input = argv[1];

    // トークナイズする
    token = tokenize();

    // パースする
    Node *node = program();

    // print_program(node);

    // コードを生成する
    codegen(node);

    return 0;
}