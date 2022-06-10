#include <stdio.h>
#include <stdlib.h>

#include "token.h"


void scan(char* line)
{}





int main()
{
    FILE *fp = fopen("program.txt", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    const short LIMIT = 80;
    char line[LIMIT];
    while (fgets(line, LIMIT, fp) != NULL)
    {
        printf("%s", line);
    }
    printf("\n");

    fclose(fp);
    return EXIT_SUCCESS;
}