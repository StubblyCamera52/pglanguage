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
ASTNode *parse_const_decl(Parser *parser);
ASTNode *parse_func_decl(Parser *parser);
ASTNode *parse_statement(Parser *parser);
ASTNode *parse_expression(Parser *parser);
// recursive descent
ASTNode *parse_assigment(Parser *parser);
ASTNode *parse_logical_or(Parser *parser);
ASTNode *parse_logical_and(Parser *parser);
ASTNode *parse_bitwise_or(Parser *parser);
ASTNode *parse_bitwise_xor(Parser *parser);
ASTNode *parse_bitwise_and(Parser *parser);
ASTNode *parse_equality(Parser *parser);
ASTNode *parse_comparison(Parser *parser);
ASTNode *parse_shift(Parser *parser);
ASTNode *parse_addition(Parser *parser);
ASTNode *parse_multiplication(Parser *parser);
ASTNode *parse_power(Parser *parser);
ASTNode *parse_unary(Parser *parser);

ASTNode *parse_postfix(Parser *parser);
ASTNode *parse_primary(Parser *parser);

#endif
