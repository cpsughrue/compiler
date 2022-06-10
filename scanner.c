#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    // grouping
    RIGHT_PAREN,
    LEFT_RAREN,

    // mathematical operations
    MINUS,
    PLUS,
    SLASH,
    STAR,

    // literals
    STRING,
    INTEGER

} token_type;

struct token
{
    token_type type;
    
};


int main()
{
    FILE *fp = fopen("program.txt", "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    char str[80];
    while (fgets(str, 80, fp) != NULL)
    {
        printf("%s", str);
        printf("%ld", strlen(str));
    }
    printf("\n");

    fclose(fp);
    return EXIT_SUCCESS;
}