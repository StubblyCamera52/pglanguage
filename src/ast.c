#include "ast.h"
#include "token.h"
#include <_string.h>
#include <stddef.h>
#include <stdlib.h>

static ASTNode *alloc_node(ASTNodeType type) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    node->type = type;
    return node;
}

ASTNode *ast_make_binary(ASTNode *left, ASTNode *right, Token op) {
    ASTNode *node = alloc_node(AST_BIN_EXPR);
    node->binary.left = left;
    node->binary.right = right;
    node-> binary.op = op;
    return node;
}

ASTNode *ast_make_identifier(Token name) {
    ASTNode *node = alloc_node(AST_IDENTIFIER);
    node->identifier.name = strdup(name.start);
    node->token = name;
    return node;
}

ASTNode *ast_make_block(ASTNode **statements, size_t count) {
    ASTNode *node = alloc_node(AST_BLOCK);
    node->block.statements = statements;
    node->block.count = count;
    return node;
}
