#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef char LEXEME_T[32];

typedef enum
{
    RIGHT_PAREN,
    LEFT_PAREN,
    MINUS,
    PLUS,
    SLASH,
    STAR,
    CARET,
    PERCENT,
    INTEGER,
    PROGRAM,
    END_OF_FILE

} TOKEN_E;

typedef struct
{
    TOKEN_E type;
    LEXEME_T lexeme; // raw substrings of source code.
    int line;
    int column;

} TOKEN;

TOKEN scan(FILE *fp);

TOKEN create_token(LEXEME_T lexeme, int line, int column, TOKEN_E type);

void print_token(TOKEN token);

#endif