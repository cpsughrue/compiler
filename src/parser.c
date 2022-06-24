#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"

PARSER data;

void print_ast(EXPR *expr)
{
    // inorder traversal of binary tree

    if (expr == NULL)
    {
        return;
    }

    if (expr->type != PRIMARY)
    {
        printf("(");
    }

    print_ast(expr->left);
    printf("%s", expr->lexeme);
    print_ast(expr->right);

    if (expr->type != PRIMARY)
    {
        printf(")");
    }

    return;
}

void print_expr(EXPR *expr)
{
    const char *OPERATOR_T_CHAR[] = {"ADD_EXPR", "SUB_EXPR", "MUL_EXPR", "DIV_EXPR", "PRIMARY", "UNKNOWN"};
    printf("%s -> %s\n", OPERATOR_T_CHAR[expr->type], expr->lexeme);
}

EXPR *create_expr(EXPR_T type, EXPR *left, EXPR *right, char *lexeme)
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
    data.curr = scan(data.fp);
}

EXPR *parse_expresion()
{
    return parse_addition();
}

EXPR *parse_addition()
{
    EXPR *expr = parse_multipication();

    while (data.curr.type == PLUS || data.curr.type == MINUS)
    {
        char operator[2];
        strcpy(operator, data.curr.lexeme);

        EXPR_T expr_t = UNKNOWN;
        switch (data.curr.type)
        {
        case PLUS:
            expr_t = ADD_EXPR;
            break;
        case MINUS:
            expr_t = SUB_EXPR;
            break;
        }

        consume();
        EXPR *right = parse_multipication();
        expr = create_expr(expr_t, expr, right, operator);
    }
    return expr;
}

EXPR *parse_multipication()
{
    EXPR *expr = parse_primary();

    while (data.curr.type == STAR || data.curr.type == SLASH)
    {
        char operator[2];
        strcpy(operator, data.curr.lexeme);

        EXPR_T expr_t = UNKNOWN;
        switch (data.curr.type)
        {
        case STAR:
            expr_t = MUL_EXPR;
            break;
        case SLASH:
            expr_t = DIV_EXPR;
            break;
        }

        consume();
        EXPR *right = parse_primary();
        expr = create_expr(expr_t, expr, right, operator);
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
    // data.prev = create_token("PROGRAM", PROGRAM);
    data.curr = scan(fp);

    EXPR *expr = parse_expresion();

    print_ast(expr);
}
