#ifndef SCANNER_H
#define SCANNER_H

#define MAX_NUM_TOKEN 100
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

    // literals
    INTEGER
} TOKEN_T;

typedef struct TOKEN
{
    TOKEN_T type;
    char lexeme[MAX_LEXEME_LEN]; // raw substrings of the source code.
} TOKEN;

void print_token(TOKEN *token);

void add_token(TOKEN *token_stream, char *lexeme, TOKEN_T type);

int scan(TOKEN *token_stream, char *line);

#endif