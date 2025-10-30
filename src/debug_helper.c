#include "debug_helper.h"
#include "ast.h"
#include <stddef.h>
#include <stdio.h>

const char* ast_node_type_to_name(ASTNodeType type) {
    switch (type) {
        case AST_BLOCK: return "AST_BLOCK";
        case AST_ASSIGNMENT: return "AST_ASSIGNMENT";
        case AST_PROGRAM: return "AST_PROGRAM";
        case AST_BIN_EXPR: return "AST_BIN_EXPR";
        case AST_UN_EXPR: return "AST_UN_EXPR";
        case AST_CONST_DECL: return "AST_CONST_DELC";
        case AST_VAR_DECL: return "AST_VAR_DECL";
        case AST_FOR: return "AST_FOR";
        case AST_IDENTIFIER: return "AST_IDENTIFIER";
        case AST_IF: return "AST_IF";
        case AST_LITERAL: return "AST_LITERAL";
        case AST_WHILE: return "AST_WHILE";
    }
}

void ast_debug(ASTNode *node, int indent) {
    if (!node) return;
    
    printf("%s\n", ast_node_type_to_name(node->type));
    
    switch (node->type) {
        case AST_BIN_EXPR: {
            ast_debug(node->binary.left,0);
            ast_debug(node->binary.right, 0);
            break;
        }
        case AST_UN_EXPR: {
            ast_debug(node->unary.expr, 0);
            break;
        }
        case AST_BLOCK: {
            for (size_t i = 0; i < node->block.count; i++) {
                ast_debug(node->block.statements[i], 0);
            }
            break;
        }
        default: break;
    }
}
