#ifndef PARSER_H
#define PARSER_H

typedef enum
{
    PLUS_EXPR,
    MINUS_EXPR,
    MULT_EXPR,
    DIV_EXPR,
    PRIMARY
} OPERATOR_T;

typedef struct expr
{
    OPERATOR_T type;

    struct expr *right;
    struct expr *left;

    char lexeme[30];
} EXPR;

typedef struct
{
    FILE *fp;
    TOKEN curr;
    TOKEN next;
} PARSER;

void print_expr(EXPR *expr);

EXPR *create_expr(OPERATOR_T type, EXPR *left, EXPR *right, char *lexeme);

void consume();

EXPR *parse_expresion();

EXPR *parse_addition();

EXPR *parse_multipication();

EXPR *parse_primary();

void parse(FILE *fp);

#endif