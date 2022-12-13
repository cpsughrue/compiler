#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "utils.h"

void print_token(TOKEN token)
{
    const char *TOKEN_T_CHAR[] =
        {
            "RIGHT_PAREN", "LEFT_PAREN",                          // grouping
            "MINUS", "PLUS", "SLASH", "STAR", "CARET", "PERCENT", // mathematical operations
            "INTEGER",                                            // literals
            "PROGRAM", "END_OF_FILE"                              // others
        };
    printf("%-11s: [%s] <line: %d, column: %d>\n", TOKEN_T_CHAR[token.type], token.lexeme, token.line, token.column);
}

TOKEN create_token(char *lexeme, int line, int column, TOKEN_T type)
{
    TOKEN new_token;

    new_token.type = type;
    new_token.line = line;
    new_token.column = column;
    strcpy(new_token.lexeme, lexeme);

    return new_token;
}

TOKEN scan(FILE *fp)
{
    static int line = 1;
    static int column = 0;

    char c = '~';
    while ((c = fgetc(fp)) != EOF)
    {
        // {c, \0, ..., \0}
        char lexeme[30] = {c, '\0'};
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
                short digit = 0;
                while (is_numeric(c))
                {
                    lexeme[digit++] = c;
                    c = fgetc(fp);
                }
                ungetc(c, fp); // move stream back to last digit
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