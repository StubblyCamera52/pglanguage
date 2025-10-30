#include "ast.h"
#include "token.h"
#include <_string.h>
#include <stddef.h>
#include <stdlib.h>

ASTNode *alloc_node(ASTNodeType type) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    node->type = type;
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
