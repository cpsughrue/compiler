#include <stdio.h>

#include "parser.h"

#define LOG_EXPR(x) print_expr(x)
// #define LOG_EXPR

void pop(FILE *fp)
{
    fprintf(fp, "\n");
    fprintf(fp, "\tpop\t\tr10\n");
    fprintf(fp, "\tpop\t\tr11\n");
}

void generate_code(EXPR *expr, FILE *fp)
{
    // post-order traversal of ast
    if (expr == NULL)
    {
        return;
    }

    generate_code(expr->left, fp);
    generate_code(expr->right, fp);

    // code gen
    switch (expr->type)
    {
    case ADD_EXPR:
        LOG_EXPR(expr);
        pop(fp);
        fprintf(fp, "\tadd\t\tr11,\tr10\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case SUB_EXPR:
        LOG_EXPR(expr);
        pop(fp);
        fprintf(fp, "\tsub\t\tr10,\tr11\n");
        fprintf(fp, "\tpush\tr11\n");
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
        fprintf(fp, "\tpush\t%s\n", expr->lexeme);
        break;

    default:
        LOG_EXPR(expr);
        break;
    }

    return;
}

void code_gen(EXPR *expr)
{

    FILE *fp = fopen("../asm/output.asm", "w");

    fprintf(fp, "\n");
    fprintf(fp, "section .text\n");
    fprintf(fp, "\tglobal _program:\n\n");
    fprintf(fp, "_program:\n\n");

    generate_code(expr, fp);

    fprintf(fp, "\n");
    fprintf(fp, "\tpop\t\tr11\n");
    fprintf(fp, "\tmov\t\trax,\tr11\n");
    fprintf(fp, "\tret");

    fclose(fp);
    return;
}
