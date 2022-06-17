#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    TOKEN token = create_token("PROGRAM", PROGRAM);
    while (token.type != END_OF_FILE)
    {
        token = scan(fp);
        print_token(token);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}