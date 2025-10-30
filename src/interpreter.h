#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
typedef struct {
    char* name;
    int value;
    struct Var* next;
} Var;

typedef struct {
    Var* head;
} Enviroment;

void interpret(ASTNode *node, Enviroment *env);
Enviroment *new_env();
void env_set(Enviroment *env, const char* name, int value);
int env_get(Enviroment *env, int value);

#endif
