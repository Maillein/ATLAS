#include "ATLAS.h"

int main(int argc, char **argv) {
    if (argc != 2)
        error("引数の数が間違っています。");

    // 入力をuser_inputに保存する
    user_input = argv[1];

    // トークナイズする
    token = tokenize();

    // パースする
    Node *node = expr();

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    // スタックトップに式全体の値が残っているはずなので
    // それをRAXにロードして関数からの返り値とする
    printf("\tpop\trax\n");
    printf("\tret\n");
    return 0;
}