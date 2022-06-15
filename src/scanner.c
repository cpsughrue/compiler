#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "utils.h"

void print_token(TOKEN *token)
{
    const char *TOKEN_T_CHAR[] =
        {
            // grouping
            "RIGHT_PAREN", "LEFT_PAREN",

            // mathematical operations
            "MINUS", "PLUS", "SLASH", "STAR",

            // literals
            "INTEGER",

            // others
            "PROGRAM"};

    printf("%s: [%s]\n", TOKEN_T_CHAR[token->type], token->lexeme);
}

TOKEN *create_token(char *lexeme, TOKEN_T type)
{
    TOKEN *new_token = (TOKEN *)malloc(sizeof(TOKEN));

    new_token->type = type;
    strcpy(new_token->lexeme, lexeme);
    new_token->next = NULL;

    return new_token;
}

TOKEN *append_token(TOKEN *last, TOKEN *new_token)
{
    if (last->next == NULL)
    {
        last->next = new_token;
        return new_token;
    }
    else
    {
        printf("append_token did not receive last token\n");
        printf("token received: ");
        print_token(last);
    }
}

void free_tokens(TOKEN *head)
{
    TOKEN *prev = head;
    TOKEN *curr = head->next;

    free(prev);
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
}

void iterate_tokens(TOKEN *head, void (*fun)(TOKEN *))
{
    TOKEN *prev = head;
    TOKEN *curr = head->next;

    (*fun)(prev);
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        (*fun)(prev);
    }
}

TOKEN *scan(FILE *fp)
{
    TOKEN *head = create_token("PROGRAM", PROGRAM);
    TOKEN *last = head;

    char c = '~';
    while ((c = fgetc(fp)) != EOF)
    {
        // {c, \0, ..., \0}
        char lexeme[30] = {c, '\0'};

        switch (c)
        {
        case '(':
            last = append_token(last, create_token(lexeme, LEFT_PAREN));
            break;

        case ')':
            last = append_token(last, create_token(lexeme, RIGHT_PAREN));
            break;

        case '+':
            last = append_token(last, create_token(lexeme, PLUS));
            break;

        case '-':
            last = append_token(last, create_token(lexeme, MINUS));
            break;

        case '/':
            last = append_token(last, create_token(lexeme, SLASH));
            break;

        case '*':
            last = append_token(last, create_token(lexeme, STAR));
            break;

        case ' ':
            break;

        case '\n':
            break;

        default:
            if (is_numeric(c))
            {
                short digit = 0;
                while (is_numeric(c))
                {
                    lexeme[digit++] = c;
                    c = fgetc(fp);
                }
                last = append_token(last, create_token(lexeme, INTEGER));
                ungetc(c, fp); // move stream back to last digit
            }
            else
            {
                printf("invalid token: %c", c);
            }

            break;
        }
    }
    return head;
}