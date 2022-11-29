#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#define MAX_LEXEME_LEN 30

typedef enum
{
    // grouping
    RIGHT_PAREN,
    LEFT_PAREN,

    // mathematical operations
    MINUS,
    PLUS,
    SLASH,
    STAR,
    CARET,
    PERCENT,

    // literals
    INTEGER,

    // other
    PROGRAM,
    END_OF_FILE
} TOKEN_T;

typedef struct
{
    TOKEN_T type;
    char lexeme[MAX_LEXEME_LEN]; // raw substrings of source code.
    int line;
    int column;
} TOKEN;

TOKEN scan(FILE *fp);

TOKEN create_token(char *lexeme, int line, int column, TOKEN_T type);

void print_token(TOKEN token);

#endif