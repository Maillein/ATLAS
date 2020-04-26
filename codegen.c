#include "ATLAS.h"

// 左辺値のアドレスを計算し、スタックに積む
static void gen_addr(Node *node) {
    if (node->kind == ND_LVAL) {
        int offset = *(node->name) - 'a' + 1;
        printf("\tlea\trax, [rbp-%d]\n", offset * 8);
        printf("\tpush\trax\n");
        return;
    }

    error("左辺地ではありません。");
}

// スタックトップにあるアドレスから値をにロードし、スタックに詰む
static void load(void) {
    printf("\tpop\trax\n");
    printf("\tmov\trax, [rax]\n");
    printf("\tpush\trax\n");
    return;
}

static void store(void) {
    printf("\tpop\trdi\n");
    printf("\tpop\trax\n");
    printf("\tmov\t[rax], rdi\n");
    printf("\tpush\trdi\n");
    return;
}

static void gen(Node *node) {
    switch (node->kind) {
        case ND_NUM:
            printf("\tpush\t%ld\n", node->val);
            return;
        case ND_LVAL:
            gen_addr(node);
            load();
            return;
        case ND_ASSIGN:
            gen_addr(node->lhs);
            gen(node->rhs);
            store();
            return;
        default:
            break;
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

    // main関数のプロローグを出力
    printf("\tpush\trbp\n");
    printf("\tmov\trbp, rsp\n");
    printf("\tsub\trsp, 208\n");

    // 抽象構文木を下りながらコード生成
    for (Node *n = node; n; n = n->next) {
        gen(n);
        printf("\tpop\trax\n");
    }

    // main関数のエピローグを出力する
    // printf("\tmov\trsp, rbp\n");
    // printf("\tpop\trbp\n");
    printf("\tleaveq\n");
    printf("\tret\n");
}