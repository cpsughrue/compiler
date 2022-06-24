#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "utils.h"

void print_token(TOKEN token)
{
    const char *TOKEN_T_CHAR[] =
        {
            "RIGHT_PAREN", "LEFT_PAREN",      // grouping
            "MINUS", "PLUS", "SLASH", "STAR", // mathematical operations
            "INTEGER",                        // literals
            "PROGRAM", "END_OF_FILE"          // others
        };
    printf("%s: [%s]\n", TOKEN_T_CHAR[token.type], token.lexeme);
}

TOKEN create_token(char *lexeme, TOKEN_T type)
{
    TOKEN new_token;

    new_token.type = type;
    strcpy(new_token.lexeme, lexeme);
    
    return new_token;
}

TOKEN scan(FILE *fp)
{
    char c = '~';
    while ((c = fgetc(fp)) != EOF)
    {
        // {c, \0, ..., \0}
        char lexeme[30] = {c, '\0'};

        switch (c)
        {
        // single character tokens
        case '(':
            return create_token(lexeme, LEFT_PAREN);
            break;
        case ')':
            return create_token(lexeme, RIGHT_PAREN);
            break;
        case '+':
            return create_token(lexeme, PLUS);
            break;
        case '-':
            return create_token(lexeme, MINUS);
            break;
        case '/':
            return create_token(lexeme, SLASH);
            break;
        case '*':
            return create_token(lexeme, STAR);
            break;

        // blank space
        case ' ':
        case '\t':
        case '\v':
        case '\r':
        case '\n':
            break;

        // multi-character length tokens
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
                return create_token(lexeme, INTEGER);
            }
            else
            {
                printf("invalid token: %c", c);
            }
            break;
        }
    }
    return create_token("EOF", END_OF_FILE);
}