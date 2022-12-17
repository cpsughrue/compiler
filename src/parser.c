#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"
#include "utils.h"

void free_ast(EXPR *expr)
{
    // postorder traversal of binary tree

    if (expr == NULL)
    {
        return;
    }

    free_ast(expr->left);
    free_ast(expr->right);
    free(expr);

    return;
}

EXPR *create_expr(EXPR_E type, EXPR *left, EXPR *right, LEXEME_T lexeme)
{
    EXPR *expr = (EXPR *)malloc(sizeof(EXPR));

    expr->type = type;
    expr->right = right;
    expr->left = left;
    strcpy(expr->lexeme, lexeme);

    print_expr(expr);
    return expr;
}

void consume(PARSER *data)
{
    data->curr = scan(data->fp);
    return;
}

EXPR *parse_expresion(PARSER *data) { return parse_addition(data); }

EXPR *parse_addition(PARSER *data)
{
    EXPR *expr = parse_multipication(data);

    while (data->curr.type == PLUS || data->curr.type == MINUS)
    {
        char operator[2];
        strcpy(operator, data->curr.lexeme);
        EXPR_E type = data->curr.type == PLUS ? ADD_EXPR : SUB_EXPR;

        consume(data);
        EXPR *right = parse_multipication(data);
        expr = create_expr(type, expr, right, operator);
    }
    return expr;
}

EXPR *parse_multipication(PARSER *data)
{
    EXPR *expr = parse_exponent(data);

    while (data->curr.type == STAR || data->curr.type == SLASH || data->curr.type == PERCENT)
    {
        char operator[2];
        strcpy(operator, data->curr.lexeme);

        EXPR_E type;
        switch (data->curr.type)
        {
        case STAR:
            type = MUL_EXPR;
            break;
        case SLASH:
            type = DIV_EXPR;
            break;
        case PERCENT:
            type = MOD_EXPR;
            break;
        default:
            break;
        }

        consume(data);
        EXPR *right = parse_exponent(data);
        expr = create_expr(type, expr, right, operator);
    }
    return expr;
}

EXPR *parse_exponent(PARSER *data)
{
    EXPR *expr = parse_primary(data);

    while (data->curr.type == CARET)
    {
        char operator[2];
        strcpy(operator, data->curr.lexeme);

        consume(data);
        EXPR *right = parse_primary(data);
        expr = create_expr(POW_EXPR, expr, right, operator);
    }
    return expr;
}

EXPR *parse_primary(PARSER *data)
{
    if (data->curr.type == LEFT_PAREN)
    {
        consume(data); // LEFT_PAREN
        EXPR *expr = parse_expresion(data);
        consume(data); // RIGHT_PAREN
        return expr;
    }
    if (data->curr.type == INTEGER)
    {
        EXPR *expr = create_expr(PRIMARY, NULL, NULL, data->curr.lexeme);
        consume(data);
        return expr;
    }
}

EXPR *parse(FILE *fp)
{
    /*

    P -> E
    E -> T((+|-)T)*
    T -> F((*|/|%)F)*
    F -> U(^U)*
    U -> int | "("E")"

    */

    PARSER data;
    data.fp = fp;
    data.curr = scan(fp);

    EXPR *expr = parse_expresion(&data);

    print_ast(expr);
    printf("\n");

    return expr;
}
