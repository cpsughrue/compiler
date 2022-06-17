#ifndef SCANNER_H
#define SCANNER_H

#define MAX_LEXEME_LEN 30

typedef enum TOKEN_T
{
    // grouping
    RIGHT_PAREN,
    LEFT_PAREN,

    // mathematical operations
    MINUS,
    PLUS,
    SLASH,
    STAR,

    // literals
    INTEGER,

    // other
    PROGRAM,
    END_OF_FILE
} TOKEN_T;

typedef struct TOKEN
{
    TOKEN_T type;
    char lexeme[MAX_LEXEME_LEN]; // raw substrings of the source code.
} TOKEN;

TOKEN scan(FILE *fp);

TOKEN create_token(char *lexeme, TOKEN_T type);

void print_token(TOKEN token);

#endif