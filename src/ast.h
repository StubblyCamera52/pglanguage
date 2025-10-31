#ifndef AST_H
#define AST_H

#include "token.h"
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    NUMBER, STRING, BOOLEAN
} EvalType;

typedef struct {
    EvalType type;
    union {
        struct {
            int result;
        } number;
        struct {
            char *result;
        } string;
        struct {
            bool result;
        } boolean;
    };
} EvalResult;

typedef struct {
    enum {
        OP, LITERAL, IDENTIFIER
    } type;
    union {
        struct {
            char *name;
        } identifier;
        struct {
            int value;
        } number;
    };
} EvalInput;

typedef enum {
  AST_PROGRAM,
  AST_VAR_DECL,
  AST_BLOCK,
  AST_IF,
  AST_WHILE,
  AST_FOR,
  AST_EXPRESSION,
  AST_IDENTIFIER
} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;
  Token token;

  union {
    struct {
      EvalInput **inputs;
    } expression;

    struct {
      struct ASTNode **statements;
      size_t count;
    } block;

    struct {
      char *name;
    } identifier;
  };
} ASTNode;

ASTNode *ast_make_identifier(Token name);
ASTNode *ast_make_block(ASTNode **statements, size_t count);
ASTNode *ast_make_expression(EvalInput **inputs);

ASTNode *alloc_node(ASTNodeType type);

#endif
