#ifndef UTILS_H
#define UTILS_H

#include "parser.h"

// #define LOG_SCAN(x)          \
//     printf("scaned token "); \
//     print_token(x);

// #define LOG_CODE_GEN(x)          \
//     printf("generaed asm for "); \
//     print_expr(x);

// #define LOG_EXPR(x)          \
//     printf("created expr "); \
//     print_expr(x);

#define LOG_SCAN(x)
#define LOG_CODE_GEN(x)
#define LOG_EXPR(x)

short is_numeric(char c);

void print_ast(EXPR *expr);

void print_expr(EXPR *expr);

void print_token(TOKEN token);

#endif