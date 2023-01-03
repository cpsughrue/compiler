#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "utils.h"

#define POSITIVE_INT 0
#define NEGATIVE_INT 1

TOKEN create_token(LEXEME_T lexeme, int line, int column, TOKEN_E type)
{
    TOKEN new_token;

    new_token.type = type;
    new_token.line = line;
    new_token.column = column;
    strcpy(new_token.lexeme, lexeme);

    return new_token;
}

int int_token(FILE *fp, LEXEME_T lexeme, char c, int column, short index)
{
    while (is_numeric(c))
    {
        lexeme[index++] = c;
        c = fgetc(fp);
        column++;
    }
    ungetc(c, fp); // move stream back to last digit
    column--;
    return column;
}

TOKEN scan(FILE *fp)
{
    // track position of last character in token
    static int line = 1;
    static int column = 1;

    // keep track of previous token
    static TOKEN_E prev;

    char c = '~';
    while ((c = fgetc(fp)) != EOF)
    {
        // {c, \0, ..., \0}
        LEXEME_T lexeme = {c, '\0'};
        column++;
        switch (c)
        {
        // single character tokens
        case '(':
            prev = LEFT_PAREN;
            return create_token(lexeme, line, column, LEFT_PAREN);
            break;
        case ')':
            prev = RIGHT_PAREN;
            return create_token(lexeme, line, column, RIGHT_PAREN);
            break;
        case '+':
            prev = PLUS;
            return create_token(lexeme, line, column, PLUS);
            break;
        case '-':
            c = fgetc(fp);
            // if next chacter is numeric make negative integer token
            if (is_numeric(c) && prev != INTEGER)
            {
                prev = INTEGER;
                column = int_token(fp, lexeme, c, column, NEGATIVE_INT);
                return create_token(lexeme, line, column, INTEGER);
            }
            ungetc(c, fp);
            prev = MINUS;
            return create_token(lexeme, line, column, MINUS);
            break;
        case '/':
            prev = SLASH;
            return create_token(lexeme, line, column, SLASH);
            break;
        case '*':
            prev = STAR;
            return create_token(lexeme, line, column, STAR);
            break;
        case '^':
            prev = CARET;
            return create_token(lexeme, line, column, CARET);
            break;
        case '%':
            prev = PERCENT;
            return create_token(lexeme, line, column, PERCENT);
            break;

        // blank space
        case ' ':
        case '\t':
        case '\v':
        case '\r':
            break;

        case '\n':
            line++;
            column = 0;
            break;

        // multi-digit number
        default:
            if (is_numeric(c))
            {
                prev = INTEGER;
                column = int_token(fp, lexeme, c, column, POSITIVE_INT);
                return create_token(lexeme, line, column, INTEGER);
            }
            else
            {
                printf("invalid token: %c\n", c);
                exit(1);
            }
            break;
        }
    }
    column++;
    return create_token("EOF", line, column, END_OF_FILE);
}