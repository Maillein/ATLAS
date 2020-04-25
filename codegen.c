#include "ATLAS.h"

void gen(Node *node) {
    if (node->kind == ND_NUM) {
        printf("\tpush\t%d\n", node->val);
        return;
    }

    gen(node->lhs);
    gen(node->rhs);

    printf("\tpop\trdi\n");
    printf("\tpop\trax\n");

    switch (node->kind) {
        case ND_ADD:
            printf("\tadd\trax, rdi\n");
            break;
        case ND_SUB:
            printf("\tsub\trax, rdi\n");
            break;
        case ND_MUL:
            printf("\timul\trax, rdi\n");
            break;
        case ND_DIV:
            printf("\tcqo\n");
            printf("\tidiv\trdi\n");
            break;
        case ND_EQ:
            printf("\tcmp\trax, rdi\n");
            printf("\tsete\tal\n");
            printf("\tmovzb\trax, al\n");
            break;
        case ND_NE:
            printf("\tcmp\trax, rdi\n");
            printf("\tsetne\tal\n");
            printf("\tmovzb\trax, al\n");
            break;
        case ND_LT:
            printf("\tcmp\trax, rdi\n");
            printf("\tsetl\tal\n");
            printf("\tmovzb\trax, al\n");
            break;
        case ND_LE:
            printf("\tcmp\trax, rdi\n");
            printf("\tsetle\tal\n");
            printf("\tmovzb\trax, al\n");
            break;
        default:
            break;
    }

    printf("\tpush\trax\n");
}

void codegen(Node *node) {
    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    for (Node *n = node; n; n = n->next) {
        gen(n);
        // スタックトップに式全体の値が残っているはずなので
        // それをRAXにロードする
        printf("\tpop\trax\n");
    }

    // RAXにはプログラムの値が入っている
    printf("\tret\n");
}