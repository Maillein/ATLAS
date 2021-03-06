#pragma once

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//  toknize.c
//

// トークンの種類
typedef enum {
    TK_RESERVED,    // 記号
    TK_IDENT,       // 識別子
    TK_NUM,         // 整数トークン
    TK_EOF,         // 入力の終わりを表すトークン
} TokenKind;


// トークン型
typedef struct Token Token;
struct Token {
    TokenKind kind;     // トークンの型
    Token *next;        // 次の入力トークン
    int val;            // kindがTK_NUMの場合、その数値
    char *str;          // トークン文字列
    unsigned int len;   // トークンの長さ
};

// プロトタイプ宣言
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
Token *consume_ident(void);
void expect(char *op);
long expect_number(void);
bool at_eof(void);
Token *tokenize(void);

// 現在着目しているトークン
extern Token *token;
// 入力プログラム
extern char *user_input;

//
//  parse.c
//

// 抽象構文木のノードの種類
typedef enum {
    ND_ADD,     // +
    ND_SUB,     // -
    ND_MUL,     // *
    ND_DIV,     // /
    ND_ASSIGN,  // =
    ND_EQ,      // ==
    ND_NE,      // !=
    ND_LT,      // <
    ND_LE,      // <=
    ND_LVAL,    // ローカル変数
    ND_NUM,     // 整数
} NodeKind;

// 抽象構文木のノードの型
typedef struct Node Node;
struct Node{
    NodeKind kind;  // ノードの型
    Node *next;     // 次のノード
    Node *lhs;      // 左辺(left-hand side)
    Node *rhs;      // 右辺(right-hand side)
    char *name;      // kindがND_VALの場合のみ使う
    long val;        // kindがND_NUMの場合のみ使う
};

// プロトタイプ宣言
Node *program(void);

//
//  toknize.c
//

// プロトタイプ宣言
void codegen(Node *node);

// main.c
void print_node(Node *node);