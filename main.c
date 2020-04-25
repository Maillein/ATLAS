#include "ATLAS.h"

int main(int argc, char **argv) {
    if (argc != 2)
        error("引数の数が間違っています。");

    // 入力をuser_inputに保存する
    user_input = argv[1];

    // トークナイズする
    token = tokenize();

    // パースする
    Node *node = program();

    // コードを生成する
    codegen(node);

    return 0;
}