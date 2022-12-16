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

} EXPR_E;

// struct is self-referential and must specify a tag
typedef struct expr
{
    EXPR_E type;
    LEXEME_T lexeme;

    struct expr *right;
    struct expr *left;

} EXPR;

typedef struct
{
    FILE *fp;
    TOKEN curr;

} PARSER;

void free_ast(EXPR *expr);

void print_ast(EXPR *expr);

void print_expr(EXPR *expr);

void consume();

EXPR *create_expr(EXPR_E type, EXPR *left, EXPR *right, LEXEME_T lexeme);

EXPR *parse_expresion();

EXPR *parse_addition();

EXPR *parse_multipication();

EXPR *parse_exponent();

EXPR *parse_primary();

EXPR *parse(FILE *fp);

#endif