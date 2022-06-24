#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    parse(fp);

    fclose(fp);
    return EXIT_SUCCESS;
}