#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"

#define MAX_LINE_LEN 240

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    TOKEN token_stream[MAX_NUM_TOKEN];

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, fp) != NULL)
    {
        scan(token_stream, line);
    }

    for(int i = 0; i < 7; i++)
    {
        print_token(&token_stream[i]);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}