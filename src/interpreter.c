#include "interpreter.h"
#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Enviroment *new_env() {
    Enviroment* env = (Enviroment*)malloc(sizeof(Enviroment));
    env->head = NULL;
    return env;
}

void env_set(Enviroment *env, const char *name, int value) {
    Var* var = env->head;
    while (var) {
        if (strcmp(var->name, name) == 0) {
            var->value = value;
            return;
        }
        var = var->next;
    }

    Var* var_new = (Var*)malloc(sizeof(Var));
    var_new->name = name;
    var_new->value = value;
    var_new->next = env->head;
    env->head = var_new;
}

int env_get(Enviroment *env, const char* name) {
    Var* var = env->head;
    while (var) {
        if (strcmp(var->name, name) == 0) {
            return var->value;
        }
        var = var->next;
    }
    return 0;
}

void env_debug_print(Enviroment *env) {
    Var* var = env->head;
    while (var) {
        printf("%s: %d\n", var->name, var->value);
    }
    return;
}

EvalResult *interpret(ASTNode *node, Enviroment *env) {
    if (!node) return NULL;

    switch (node->type) {
        case AST_BLOCK: {
            printf("AST_BLOCK\n");
            for (size_t i = 0; i < node->block.count; i++) {
                interpret(node->block.statements[i], env);
            }
        }
        case AST_EXPRESSION: {
            return NULL;
        }
        default: printf("invalid node type\n");
    }
}
