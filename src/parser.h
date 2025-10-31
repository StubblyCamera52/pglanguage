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

// grammar parsers (recursive)
ASTNode *parse_program(Parser *parser);
ASTNode *parse_declaration(Parser *parser);
ASTNode *parse_var_decl(Parser *parser);
ASTNode *parse_statement(Parser *parser);
ASTNode *parse_expression_stmt(Parser *parser);

ASTNode *parse_expression(Parser *parser);

ASTNode *parse_postfix(Parser *parser);
ASTNode *parse_primary(Parser *parser);

#endif
