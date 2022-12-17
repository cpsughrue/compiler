#include "parser.h"

short is_numeric(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
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

const char *getEXPR_E(EXPR_E expr_type)
{
    switch (expr_type)
    {
    case ADD_EXPR:
        return "ADD_EXPR";
    case SUB_EXPR:
        return "SUB_EXPR";
    case MUL_EXPR:
        return "MUL_EXPR";
    case DIV_EXPR:
        return "DIV_EXPR";
    case POW_EXPR:
        return "POW_EXPR";
    case MOD_EXPR:
        return "MOD_EXPR";
    case PRIMARY:
        return "PRIMARY";
    case UNKNOWN:
        return "UNKOWN";
    default:
        return "SOMETHING IS WRONG: tried to print expression type that doesn't exist";
    }
}

const char *getTOKEN_E(TOKEN_E token_type)
{
    switch (token_type)
    {
    case RIGHT_PAREN:
        return "RIGHT_PAREN";
    case LEFT_PAREN:
        return "LEFT_PAREN";
    case MINUS:
        return "MINUS";
    case PLUS:
        return "PLUS";
    case SLASH:
        return "SLASH";
    case STAR:
        return "STAR";
    case CARET:
        return "CARET";
    case PERCENT:
        return "PERCENT";
    case INTEGER:
        return "INTEGER";
    case PROGRAM:
        return "PROGRAM";
    case END_OF_FILE:
        return "END_OF_FILE";
    default:
        return "SOMETHING IS WRONG: tried to print token type that doesn't exist";
    }
}

void print_expr(EXPR *expr)
{
    printf("%s -> %s\n", getEXPR_E(expr->type), expr->lexeme);
    return;
}

void print_token(TOKEN token)
{
    printf("%-11s: [%s] <line: %d, column: %d>\n", getTOKEN_E(token.type), token.lexeme, token.line, token.column);
    return;
}
