#include "interpreter.h"
#include "stack.h"
#include "token.h"
#include <_string.h>
#include <stdbool.h>
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
      StackItem item;
      item.type = LITERAL;
      item.literal.value = atoi(value);
      push(&stack, item);
      free(value);
      i++;
      break;
    }
    case TOKEN_IDENTIFIER: {
      char *name = (char *)malloc(token.length + 1);
      strncpy(name, token.start, token.length);
      name[token.length] = '\0';

      StackItem item;
      item.type = IDENT;
      item.ident.name = name;
      push(&stack, item);
      i++;
      break;
    }
    case TOKEN_EQUAL: {
      StackItem value = pop(&stack);
      StackItem var = pop(&stack);

      env_set(env, var.ident.name, value.literal.value);
      i++;
      break;
    }
    case TOKEN_PLUS: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = v1 + v2;

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_MINUS: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = v1 - v2;

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_DIVIDE: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = v1 / v2;

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_MULTIPLY: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = v1 * v2;

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_LEFTBRACE: {
      int depth = 1;
      int j = i;
      while (tokens[j].type != TOKEN_RIGHTBRACE || depth > 1) {
        j++;
        // printf("J: %d\n", j);
        if (tokens[j].type == TOKEN_LEFTBRACE) {
          depth++;
        }
        if (tokens[j].type == TOKEN_RIGHTBRACE) {
          depth--;
        }
      }

      j -= i;

      // printf("J: %d\n", j);

      Token *scoped_tokens = (Token *)malloc(sizeof(Token) * j);

      j = 0;

      depth = 1;

      while (tokens[i].type != TOKEN_RIGHTBRACE || depth > 1) {
        i++;
        if (tokens[i].type == TOKEN_LEFTBRACE) {
          depth++;
        }
        if (tokens[i].type == TOKEN_RIGHTBRACE) {
          depth--;
        }
        scoped_tokens[j] = tokens[i];
        j++;
      }

      StackItem item;
      item.type = BLOCK;
      item.block.tokens = scoped_tokens;
      item.block.size = j;

      push(&stack, item);
      break;
    }
    case TOKEN_IF: {
      StackItem condition = pop(&stack);
      StackItem block = pop(&stack);

      if (block.type != BLOCK) {
        break;
      }

      if (condition.literal.value == 1) {
        interpret(block.block.tokens, env, block.block.size);
      }

      i++;
      break;
    }
    case TOKEN_LESS: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = (v1 < v2);

      // printf("%d: %d < %d\n", result, v1, v2);

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_GREATER: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = (v1 > v2);

      // printf("%d: %d < %d\n", result, v1, v2);

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    case TOKEN_EQUALEQUAL: {
      StackItem n1 = pop(&stack);
      StackItem n2 = pop(&stack);
      int v1 = 0;
      int v2 = 0;

      if (n1.type == IDENT) {
        v1 = env_get(env, n1.ident.name);
      } else {
        v1 = n1.literal.value;
      }

      if (n2.type == IDENT) {
        v2 = env_get(env, n2.ident.name);
      } else {
        v2 = n2.literal.value;
      }

      int result = (v1 == v2);

      // printf("%d: %d < %d\n", result, v1, v2);

      push(&stack, st_from_int(result));
      i++;
      break;
    }
    default:
      i++;
    };
  }
end_loop:
  (void)0; // prevents compiler warnign
}
