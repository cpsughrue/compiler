#ifndef UTILS_H
#define UTILS_H

#include "parser.h"

#ifdef VERBOSE

#define LOG_TOKEN(msg, TOKEN) \
    printf(msg);              \
    print_token(TOKEN);

#define LOG_EXPR(msg, EXPR) \
    printf(msg);            \
    print_expr(EXPR);

#define LOG(...)                             \
    printf("%s [%d]: ", __FILE__, __LINE__); \
    printf(__VA_ARGS__);

#else

#define LOG_TOKEN(msg, x)
#define LOG_EXPR(msg, x)
#define LOG(...)

#endif

short is_numeric(char c);

void print_ast(EXPR *expr);

void print_expr(EXPR *expr);

void print_token(TOKEN token);

void print_red();

void reset_color();

#endif