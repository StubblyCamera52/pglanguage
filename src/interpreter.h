#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "token.h"
typedef struct {
    char* name;
    int value;
    struct Var* next;
} Var;

typedef struct {
    Var* head;
} Enviroment;

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

EvalResult *interpret(ASTNode *node, Enviroment *env);
EvalResult *evaluate(Token **tokens);
Enviroment *new_env();
void env_set(Enviroment *env, const char* name, int value);
int env_get(Enviroment *env, const char* name);

#endif
