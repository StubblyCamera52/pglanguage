// thank you wikipedia https://en.wikipedia.org/wiki/Recursive_descent_parser

#include "parser.h"
#include "ast.h"
#include "token.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void parser_init(Parser *parser, Token *tokens, size_t count) {
    parser->tokens = tokens;
    parser->count = count;
    parser->current = 0;
}

Token *peek(Parser *parser) {
    if (parser->current >= parser->count) return &parser->tokens[parser->count-1]; // eof token
    return &parser->tokens[parser->current];
}

Token *previous(Parser *parser) {
    if (parser->current == 0) return NULL;
    return &parser->tokens[parser->current-1]
}

Token *advance(Parser *parser) {
    if (parser->current < parser->count) parser->current++;
    return previous(parser);
}

bool check(Parser *parser, TokenType type) {
    if (parser->current >= parser->count) return false;
    return peek(parser)->type == type;
}

bool match(Parser *parser, TokenType type) {
    if (check(parser, type)) {
        advance(parser);
        return true;
    };
    return false;
}

// mess of recursion for grammar rules

ASTNode *parse_primary(Parser *parser);

ASTNode *parse_assignment(Parser *parser) {
    ASTNode *expr = parse_primary(parser);

    if (match(parser, TOKEN_EQUAL)) {
        Token op = *previous(parser);
        ASTNode *right = parse_assignment(parser);
        expr = ast_make_binary(expr, right, op)
    }

    return expr;
}

ASTNode *parse_primary(Parser *parser) {
    if (match(parser, TOKEN_IDENTIFIER)) {
        return ast_make_identifier(*previous(parser));
    }
}

ASTNode *parse_var_decl(Parser *parser) {
    Token name = *previous(parser);

    ASTNode *initializer = NULL; // initializer is optional
    if (match(parser, TOKEN_EQUAL)) {
        initializer = parse_expr
    }
}

// start of tree
ASTNode *parse_declaration(Parser *parser) {
    if (match(parser, TOKEN_VAR)) {
        return parse_var_decl(parser);
    }
}

ASTNode *parse_expression(Parser *parser) {
    // start parse from highest grammar level
    parse_assignment(parser);
}

ASTNode *parse_program(Parser *parser) {
    ASTNode **statements = NULL;
    size_t count = 0;

    while (!check(parser, TOKEN_EOF)) {
        ASTNode *stmt = parse_declaration(parser);

        statements = realloc(statements, sizeof(ASTNode*)*(count+1));
        statements[count++] = stmt;
    }

    return ast_make_block(statements, count);
}
