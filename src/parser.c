// thank you wikipedia https://en.wikipedia.org/wiki/Recursive_descent_parser

#include "parser.h"
#include "ast.h"
#include "token.h"
#include <stddef.h>
#include <stdbool.h>

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

ASTNode *parse_program(Parser *parser) {
    ASTNode **statements = NULL;
    size_t count = 0;

    while (!check(parser, TOKEN_EOF)) {
        ASTNode *stmt;
    }
}

// start of tree
ASTNode *parse_declaration(Parser *parser) {

}
