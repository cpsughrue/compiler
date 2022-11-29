#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "parser.h"

void generate_code(EXPR *expr, FILE *fp);
void code_gen(EXPR *expr);
void pop(FILE *fp);

#endif