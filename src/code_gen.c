#include <stdio.h>

#include "parser.h"

#define LOG_EXPR(x) print_expr(x)
// #define LOG_EXPR

void pop(FILE *fp)
{
    fprintf(fp, "\n");
    fprintf(fp, "\tpop\t\tr10\n");
    fprintf(fp, "\tpop\t\tr11\n");
    fprintf(fp, "\n");
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

    /*
    In some cases labels are created in the assemble.
    To differentiate lables with the same funtionality
    append an int at the end.
    */
    static int mangler = 0;

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
        fprintf(fp, "\tsub\t\tr11,\tr10\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case MUL_EXPR:
        LOG_EXPR(expr);
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\timul\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trax\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case DIV_EXPR:
        LOG_EXPR(expr);
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\tidiv\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trax\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case POW_EXPR:
        LOG_EXPR(expr);
        pop(fp);
        fprintf(fp, "\tcmp\t\tr10,\t0\n");
        fprintf(fp, "\tjne\t\tpow_%d\n\n", mangler);

        fprintf(fp, "\tmov\t\trax,\t1\n");
        fprintf(fp, "\tjmp\t\tpow_end_%d\n\n", mangler);

        fprintf(fp, "\tpow_%d:\n\n", mangler);

        fprintf(fp, "\t\tmov\t\trax,\tr11\n");
        fprintf(fp, "\t\tmov\t\tr12,\t1\n\n");

        fprintf(fp, "\tpow_loop_%d:\n\n", mangler);

        fprintf(fp, "\t\tcmp\t\tr12,\tr10\n");
        fprintf(fp, "\t\tje\t\tpow_end_%d\n\n", mangler);

        fprintf(fp, "\t\tinc\t\tr12\n");
        fprintf(fp, "\t\timul\tr11\n\n");

        fprintf(fp, "\t\tjmp\t\tpow_loop_%d\n\n", mangler);

        fprintf(fp, "\tpow_end_%d:\n\n", mangler);

        fprintf(fp, "\t\tmov\tr11,\trax\n");
        fprintf(fp, "\t\tpush\tr11\n\n");

        mangler++;
        break;

    case MOD_EXPR:
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\tidiv\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trdx\n");
        fprintf(fp, "\tpush\tr11\n");
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

    FILE *fp = fopen("../asm/program.asm", "w");

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
