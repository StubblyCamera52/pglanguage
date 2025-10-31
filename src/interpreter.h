#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "token.h"

typedef struct Var {
    char* name;
    int value;
    struct Var* next;
} Var;

typedef struct {
    Var* head;
} Enviroment;

void interpret(Token *tokens, Enviroment *env, int num_tokens);
Enviroment *new_env();
void env_set(Enviroment *env, const char* name, int value);
int env_get(Enviroment *env, const char* name);

#endif
