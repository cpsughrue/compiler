#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

void print_token(TOKEN *token)
{
    const char *TOKEN_T_CHAR[] =
        {
            // grouping
            "RIGHT_PAREN", "LEFT_PAREN",

            // mathematical operations
            "MINUS", "PLUS", "SLASH", "STAR",

            // literals
            "INTEGER"};

    printf("%s: [%s]\n", TOKEN_T_CHAR[token->type], token->lexeme);
}

void add_token(TOKEN *token_stream, char *lexeme, TOKEN_T type)
{
    static int i = 0;

    if (i < MAX_NUM_TOKEN)
    {
        TOKEN token;

        token.type = type;
        strcpy(token.lexeme, lexeme);

        token_stream[i++] = token;
    }
    else
    {
        printf("number of tokens exceeded maximum amount (max amt: %d)", MAX_NUM_TOKEN);
        exit(0);
    }
}

void scan(TOKEN *token_stream, char *line)
{
    short curr = 0;
    while (curr < strlen(line))
    {
        char lexeme[MAX_LEXEME_LEN] = "\0"; // {\0, ..., \0}
        lexeme[0] = line[curr];

        switch (line[curr])
        {
        case ')':
            add_token(token_stream, lexeme, RIGHT_PAREN);
            break;

        case '(':
            add_token(token_stream, lexeme, LEFT_PAREN);
            break;

        case '+':
            add_token(token_stream, lexeme, PLUS);
            break;

        case '-':
            add_token(token_stream, lexeme, MINUS);
            break;

        case '*':
            add_token(token_stream, lexeme, STAR);
            break;

        case '/':
            add_token(token_stream, lexeme, SLASH);
            break;

        case ' ':
            break;
            
        case '\n':
            break;

        default:
            if (line[curr] >= 48 && line[curr] <= 57)
            {
                short digit = 0;
                do
                {
                    lexeme[digit++] = line[curr++];
                } while (line[curr] >= 48 && line[curr] <= 57);
                
                add_token(token_stream, lexeme, INTEGER);
                curr--; // move current back to last digit
            }
            else
            {
                printf("invalid token: %c\n", line[curr]);
            }
            break;
        }
        curr++;
    }
}
