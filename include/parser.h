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

void consume(PARSER *data);

EXPR *parse_expresion(PARSER *data);

EXPR *parse_addition(PARSER *data);

EXPR *parse_multipication(PARSER *data);

EXPR *parse_exponent(PARSER *data);

EXPR *parse_primary(PARSER *data);

EXPR *parse(FILE *fp);

EXPR *create_expr(EXPR_E type, EXPR *left, EXPR *right, LEXEME_T lexeme);

#endif