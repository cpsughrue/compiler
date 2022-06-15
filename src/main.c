#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file can't be opened \n");
        return EXIT_FAILURE;
    }

    TOKEN *head = scan(fp);
    // print_all_tokens(head);

    iterate_tokens(head, print_token);

    free_tokens(head);

    fclose(fp);
    return EXIT_SUCCESS;
}