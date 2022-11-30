#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"

PARSER data;

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
    const char *OPERATOR_T_CHAR[] = {"ADD_EXPR", "SUB_EXPR", "MUL_EXPR",
                                     "DIV_EXPR", "POW_EXPR", "MOD_EXPR",
                                     "PRIMARY", "UNKNOWN"};
    printf("%s -> %s\n", OPERATOR_T_CHAR[expr->type], expr->lexeme);
    return;
}

EXPR *create_expr(EXPR_TYPE type, EXPR *left, EXPR *right, char *lexeme)
{
    EXPR *expr = (EXPR *)malloc(sizeof(EXPR));

    expr->type = type;
    expr->right = right;
    expr->left = left;
    strcpy(expr->lexeme, lexeme);

    print_expr(expr);
    return expr;
}

void consume()
{
    print_token(data.curr);
    data.curr = scan(data.fp);
    return;
}

EXPR *parse_expresion() { return parse_addition(); }

EXPR *parse_addition()
{
    EXPR *expr = parse_multipication();

    while (data.curr.type == PLUS || data.curr.type == MINUS)
    {
        char operator[2];
        strcpy(operator, data.curr.lexeme);
        EXPR_TYPE expr_t = data.curr.type == PLUS ? ADD_EXPR : SUB_EXPR;

        consume();
        EXPR *right = parse_multipication();
        expr = create_expr(expr_t, expr, right, operator);
    }
    return expr;
}

EXPR *parse_multipication()
{
    EXPR *expr = parse_exponent();

    while (data.curr.type == STAR || data.curr.type == SLASH ||
           data.curr.type == PERCENT)
    {
        char operator[2];
        strcpy(operator, data.curr.lexeme);

        EXPR_TYPE expr_t;
        switch (data.curr.type)
        {
        case STAR:
            expr_t = MUL_EXPR;
            break;
        case SLASH:
            expr_t = DIV_EXPR;
            break;
        case PERCENT:
            expr_t = MOD_EXPR;
            break;
        default:
            break;
        }

        consume();
        EXPR *right = parse_exponent();
        expr = create_expr(expr_t, expr, right, operator);
    }
    return expr;
}

EXPR *parse_exponent()
{
    EXPR *expr = parse_primary();

    while (data.curr.type == CARET)
    {
        char operator[2];
        strcpy(operator, data.curr.lexeme);

        consume();
        EXPR *right = parse_primary();
        expr = create_expr(POW_EXPR, expr, right, operator);
    }
    return expr;
}

EXPR *parse_primary()
{
    if (data.curr.type == LEFT_PAREN)
    {
        consume(); // LEFT_PAREN
        EXPR *expr = parse_expresion();
        consume(); // RIGHT_PAREN
        return expr;
    }
    if (data.curr.type == INTEGER)
    {
        EXPR *expr = create_expr(PRIMARY, NULL, NULL, data.curr.lexeme);
        consume();
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

    data.fp = fp;
    data.curr = scan(fp);

    EXPR *expr = parse_expresion();

    print_ast(expr);
    printf("\n");

    return expr;
}
