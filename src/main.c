#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "code_gen.h"
#include "scanner.h"
#include "parser.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    // options set dependent on flags provided by user
    bool FLAG_SCAN_ONLY = false;
    bool INVALID_FLAG = false;

    short file_index = 0;

    // procces command line arguments
    // argv[0] is the name of the program and can be skipped
    for (short i = 1; i < argc; i++)
    {
        // process flags
        if (argv[i][0] == '-')
        {
            // argv[i][0] is - and can be skipped
            for (short j = 1; j < strlen(argv[i]); j++)
            {
                switch (argv[i][j])
                {
                case 's':
                    FLAG_SCAN_ONLY = true;
                    break;
                default:
                    printf("-%c is an invalid flag\n", argv[i][j]);
                    INVALID_FLAG = true;
                    break;
                }
            }
        }
        // record file path index in argv
        else
        {
            file_index = i;
        }
        if (INVALID_FLAG == true)
        {
            return EXIT_FAILURE;
        }
    }

    // check that non flag argument was provided
    // if not ask for a file path to program
    if (file_index == 0)
    {
        printf("must provide a file path\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[file_index], "r");
    if (fp == NULL)
    {
        printf("%s can't be opened \n", argv[file_index]);
        return EXIT_FAILURE;
    }

    if (FLAG_SCAN_ONLY == true)
    {
        TOKEN token = create_token("PROGRAM", 0, 0, PROGRAM);
        while (token.type != END_OF_FILE)
        {
            token = scan(fp);
            LOG_SCAN(token);
        }
    }
    else
    {
        // generate AST
        EXPR *ast = parse(fp);

        // generate 64bit x86-64 Intel Syntax assembly
        code_gen(ast);

        // free AST and close file
        free_ast(ast);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}