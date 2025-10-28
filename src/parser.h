#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "token.h"
#include <stddef.h>

typedef struct {
    Token *tokens; // list of tokens
    size_t current; // current index
    size_t count; // total num of tokens
} Parser ;

void parser_init(Parser *parser, Token *tokens, size_t count);
ASTNode *parse_program(Parser *parser);

#endif
