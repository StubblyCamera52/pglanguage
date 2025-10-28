#ifndef AST_H
#define AST_H


#include "token.h"
#include <stddef.h>

typedef enum {
    AST_PROGRAM, AST_VAR_DECL, AST_CONST_DECL, AST_BLOCK, AST_IF, AST_WHILE, AST_FOR, AST_BIN_EXPR, AST_UN_EXPR, AST_ASSIGNMENT, AST_LITERAL, AST_IDENTIFIER
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    Token token;

    union {
      struct {
          struct ASTNode *left;
          struct ASTNode *right;
          Token op;
      } binary;

      struct {
          struct ASTNode *expr;
          Token op;
      } unary;

      struct {
          struct ASTNode **statements;
          size_t count;
      } block;

      struct {
          char *value;
      } literal;

      struct {
          char *name;
      } identifier;
    };
} ASTNode;

ASTNode *ast_make_identifier(Token name);
ASTNode *ast_make_binary(ASTNode *left, ASTNode *right, Token op);
ASTNode *ast_make_block(ASTNode **statements, size_t count);

ASTNode *alloc_node(ASTNodeType type);

#endif
