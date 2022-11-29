
#include "parser.h"

#define LOG_EXPR(x) print_expr(x)
//#undef LOG_EXPR

void generate_code(EXPR *expr)
{

    // post-order traversal of ast

    if (expr == NULL)
    {
        return;
    }

    generate_code(expr->left);
    generate_code(expr->right);

    // code gen
    switch (expr->type)
    {
    case ADD_EXPR:
        LOG_EXPR(expr);
        break;

    case SUB_EXPR:
        LOG_EXPR(expr);
        break;

    case MUL_EXPR:
        LOG_EXPR(expr);
        break;

    case DIV_EXPR:
        LOG_EXPR(expr);
        break;

    case POW_EXPR:
        LOG_EXPR(expr);
        break;

    case MOD_EXPR:
        LOG_EXPR(expr);
        break;

    case PRIMARY:
        LOG_EXPR(expr);
        break;

    default:
        LOG_EXPR(expr);
        break;
    }

    return;
}
