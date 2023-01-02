#include <stdio.h>

#include "parser.h"
#include "utils.h"

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
    In some cases labels are created in the assembly.
    To differentiate lables append an int at the end.
    */
    static int mangler = 0;

    // code gen
    switch (expr->type)
    {
    case ADD_EXPR:
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\tadd\t\tr11,\tr10\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case SUB_EXPR:
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\tsub\t\tr11,\tr10\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case MUL_EXPR:
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\timul\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trax\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case DIV_EXPR:
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\tidiv\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trax\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case POW_EXPR:
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\t; if the exponent is zero\n");
        fprintf(fp, "\tcmp\t\tr10,\t0\n");
        fprintf(fp, "\tje\t\tzero_exponent_%d\n\n", mangler);

        fprintf(fp, "\t; if exponent is greater than zero\n");
        fprintf(fp, "\tcmp\t\tr10,\t0\n");
        fprintf(fp, "\tjg\t\tpow_%d\n\n", mangler);

        fprintf(fp, "\tnegative_exponent_%d:\n", mangler);
        fprintf(fp, "\t\tmov\t\trax, 0\n");
        fprintf(fp, "\t\tjmp\t\tpow_end_%d\n\n", mangler);

        fprintf(fp, "\tzero_exponent_%d:\n", mangler);
        fprintf(fp, "\t\tmov\t\trax,\t1\n");
        fprintf(fp, "\t\tjmp\t\tpow_end_%d\n\n", mangler);

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
        LOG_EXPR("generating asm for", expr);
        pop(fp);
        fprintf(fp, "\tmov\t\trax,\tr11\n");
        fprintf(fp, "\tidiv\tr10\n");
        fprintf(fp, "\tmov\t\tr11,\trdx\n");
        fprintf(fp, "\tpush\tr11\n");
        break;

    case PRIMARY:
        LOG_EXPR("generating asm for", expr);
        fprintf(fp, "\tpush\t%s\n", expr->lexeme);
        break;

    default:
        LOG_EXPR("generating asm for", expr);
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
