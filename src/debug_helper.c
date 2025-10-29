#include "debug_helper.h"
#include "ast.h"
#include <stddef.h>
#include <stdio.h>

void debug_print_ast_tree(ASTNode *node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    printf("|-- %s\n", node->token.start);

    switch (node->type) {
        case AST_BLOCK: {
            for (size_t i = 0; i < node->block.count; i++) {
                debug_print_ast_tree(node->block.statements[i], indent+1);
            }
        }
        case AST_BIN_EXPR: {
            debug_print_ast_tree(node->binary.left, indent+1);
            debug_print_ast_tree(node->binary.right, indent+1);
        }
    }
}
