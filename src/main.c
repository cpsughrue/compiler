#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "code_gen.h"

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    // genrate AST
    EXPR *ast = parse(fp);

    // generate 64bit x86-64 Intel Syntax assembly
    code_gen(ast);

    // free AST and close file
    free_ast(ast);
    fclose(fp);

    return EXIT_SUCCESS;
}