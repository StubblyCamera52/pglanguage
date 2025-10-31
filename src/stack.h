#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

#include <stdbool.h>

typedef enum { IDENT, LITERAL } StackType;

typedef struct {
  StackType type;
  union {
    struct {
        int value;
    } literal;
    struct {
        char* name;
    } ident;
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

#endif
