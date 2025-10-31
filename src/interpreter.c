#include "interpreter.h"
#include "stack.h"
#include "token.h"
#include <_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Enviroment *new_env() {
  Enviroment *env = (Enviroment *)malloc(sizeof(Enviroment));
  env->head = NULL;
  return env;
}

void env_set(Enviroment *env, const char *name, int value) {
  Var *var = env->head;
  while (var) {
    if (strcmp(var->name, name) == 0) {
      var->value = value;
      return;
    }
    var = var->next;
  }

  Var *var_new = (Var *)malloc(sizeof(Var));
  var_new->name = strdup(name);
  var_new->value = value;
  var_new->next = env->head;
  env->head = var_new;
}

int env_get(Enviroment *env, const char *name) {
  Var *var = env->head;
  while (var) {
    if (strcmp(var->name, name) == 0) {
      return var->value;
    }
    var = var->next;
  }
  return 0;
}

void env_debug_print(Enviroment *env) {
  Var *var = env->head;
  while (var) {
    printf("ENVIROMENT:\n");
    printf("%s: %d\n", var->name, var->value);
    var = var->next;
  }
  return;
}

void interpret(Token *tokens, Enviroment *env, int num_tokens) {
  Stack stack;
  initialize_stack(&stack);

  for (int i = 0; i < num_tokens;) {
    Token token = tokens[i];

    switch (token.type) {
    case TOKEN_EOF:
      goto end_loop;
    case TOKEN_VAR: {
      Token name_token = tokens[i + 1];
      char *name = (char *)malloc(name_token.length + 1);
      strncpy(name, name_token.start, name_token.length);
      name[name_token.length] = '\0';
      env_set(env, name, 0);
      free(name);
      i += 2;
      break;
    }
    case TOKEN_NUMBER: {
      char *value = (char *)malloc(token.length);
      strncpy(value, token.start, token.length);
      push(&stack, atoi(value));
      free(value);
      i++;
      break;
    }
    case TOKEN_IDENTIFIER: {
      char *name = (char *)malloc(token.length + 1);
      strncpy(name, token.start, token.length);
      name[token.length] = '\0';
      int value = env_get(env, name);
      push(&stack, value);
    }
    default:
      i++;
    };
  }
end_loop:

  env_debug_print(env);
  print_stack(&stack);
}
