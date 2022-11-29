#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"

typedef enum
{
    ADD_EXPR,
    SUB_EXPR,
    MUL_EXPR,
    DIV_EXPR,
    POW_EXPR,
    MOD_EXPR,
    PRIMARY,
    UNKNOWN
} EXPR_TYPE;

typedef struct expr
{
    EXPR_TYPE type;

    struct expr *right;
    struct expr *left;

    char lexeme[30];
} EXPR;

typedef struct
{
    FILE *fp;
    TOKEN curr;
} PARSER;

void free_ast(EXPR *expr);

void print_ast(EXPR *expr);

void print_expr(EXPR *expr);

EXPR *create_expr(EXPR_TYPE type, EXPR *left, EXPR *right, char *lexeme);

void consume();

EXPR *parse_expresion();

EXPR *parse_addition();

EXPR *parse_multipication();

EXPR *parse_exponent();

EXPR *parse_primary();

EXPR *parse(FILE *fp);

#endif