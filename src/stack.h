#ifndef STACK_H
#define STACK_H

#include "token.h"
#define MAX_STACK_SIZE 100

#include <stdbool.h>

typedef enum { IDENT, LITERAL, BLOCK } StackType;

typedef struct {
  StackType type;
  union {
    struct {
        int value;
    } literal;
    struct {
        char* name;
    } ident;
    struct {
        Token* tokens;
        int size;
    } block;
  };
} StackItem;

typedef struct {
  StackItem array[MAX_STACK_SIZE];
  int top;
} Stack;

void initialize_stack(Stack *stack);
bool stack_empty(Stack *stack);
void push(Stack *stack, StackItem value);
StackItem pop(Stack *stack);
StackItem peek(Stack *stack);
void print_stack(Stack *stack);
StackItem st_from_int(int value);


#endif
