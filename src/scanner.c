#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "utils.h"

TOKEN create_token(LEXEME_T lexeme, int line, int column, TOKEN_E type)
{
    TOKEN new_token;

    new_token.type = type;
    new_token.line = line;
    new_token.column = column;
    strcpy(new_token.lexeme, lexeme);

    return new_token;
}

void int_token(FILE *fp, LEXEME_T lexeme, char c, short index)
{
    while (is_numeric(c))
    {
        lexeme[index++] = c;
        c = fgetc(fp);
    }
    ungetc(c, fp); // move stream back to last digit
}

TOKEN scan(FILE *fp)
{
    static int line = 1;
    static int column = 0;

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
            return create_token(lexeme, line, column, LEFT_PAREN);
            break;
        case ')':
            return create_token(lexeme, line, column, RIGHT_PAREN);
            break;
        case '+':
            return create_token(lexeme, line, column, PLUS);
            break;
        case '-':
            c = fgetc(fp);
            if (is_numeric(c))
            {
                int_token(fp, lexeme, c, 1);
                return create_token(lexeme, line, column, INTEGER);
            }
            ungetc(c, fp);
            return create_token(lexeme, line, column, MINUS);
            break;
        case '/':
            return create_token(lexeme, line, column, SLASH);
            break;
        case '*':
            return create_token(lexeme, line, column, STAR);
            break;
        case '^':
            return create_token(lexeme, line, column, CARET);
            break;
        case '%':
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
                int_token(fp, lexeme, c, 0);
                return create_token(lexeme, line, column, INTEGER);
            }
            else
            {
                printf("invalid token: %c", c);
                exit(0);
            }
            break;
        }
    }
    column++;
    return create_token("EOF", line, column, END_OF_FILE);
}