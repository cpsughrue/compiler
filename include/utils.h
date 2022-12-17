#ifndef UTILS_H
#define UTILS_H

#include "parser.h"

short is_numeric(char c);

void print_ast(EXPR *expr);

void print_expr(EXPR *expr);

void print_token(TOKEN token);

#endif