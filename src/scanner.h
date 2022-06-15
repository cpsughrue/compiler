#ifndef SCANNER_H
#define SCANNER_H

#define MAX_NUM_TOKEN 100
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
    PROGRAM

} TOKEN_T;

typedef struct TOKEN
{
    TOKEN_T type;
    char lexeme[MAX_LEXEME_LEN]; // raw substrings of the source code.
    struct TOKEN *next;
} TOKEN;

TOKEN *scan(FILE *fp);

TOKEN *create_token(char *lexeme, TOKEN_T type);

TOKEN *append_token(TOKEN *head, TOKEN *new_token);

void iterate_tokens(TOKEN *head, void (*fun)(TOKEN *));

void free_tokens(TOKEN *head);

void print_token(TOKEN *token);

#endif