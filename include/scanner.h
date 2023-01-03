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
    int line;        // line of token
    int column;      // last column of token

} TOKEN;

TOKEN scan(FILE *fp);

TOKEN create_token(LEXEME_T lexeme, int line, int column, TOKEN_E type);

int int_token(FILE *fp, LEXEME_T lexeme, char c, int column, short index);

void print_token(TOKEN token);

#endif