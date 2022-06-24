#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"

PARSER data;

void print_expr(EXPR *expr)
{
    const char *OPERATOR_T_CHAR[] = {"PLUS_EXPR", "MINUS_EXPR", "MULT_EXPR", "DIV_EXPR", "PRIMARY"};
    printf("%s -> %s\n", OPERATOR_T_CHAR[expr->type], expr->lexeme);
}

EXPR *create_expr(OPERATOR_T type, EXPR *left, EXPR *right, char *lexeme)
{
    EXPR *expr = (EXPR *)malloc(sizeof(EXPR));

    expr->type = type;
    expr->right = right;
    expr->left = left;
    strcpy(expr->lexeme, lexeme);

    return expr;
}

void consume()
{
    data.curr = data.next;
    data.next = scan(data.fp);
}

EXPR *parse_expresion()
{
    return parse_addition();
}

EXPR *parse_addition()
{
    EXPR *expr = parse_multipication();

    while (data.curr.type == PLUS)
    {
        consume();
        EXPR *right = parse_multipication();
        expr = create_expr(PLUS_EXPR, expr, right, "+");
    }
    return expr;
}

EXPR *parse_multipication()
{
    EXPR *expr = parse_primary();

    while (data.curr.type == STAR)
    {
        consume();
        EXPR *right = parse_primary();
        expr = create_expr(MULT_EXPR, expr, right, "*");
    }
    return expr;
}

EXPR *parse_primary()
{
    EXPR *expr = create_expr(PRIMARY, NULL, NULL, data.curr.lexeme);
    consume();
    return expr;
}

void parse(FILE *fp)
{
    /*

    P -> E
    E -> T{{+|-}T}*
    T -> F{{*|/}F}*
    F -> int | (E)

    */

    data.fp = fp;
    data.curr = scan(fp);
    data.next = scan(fp);

    EXPR *expr = parse_expresion();
}
