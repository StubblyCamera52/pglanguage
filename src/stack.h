#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

#include <stdbool.h>

typedef struct {
  int array[MAX_STACK_SIZE];
  int top;
} Stack;

void initialize_stack(Stack *stack);
bool stack_empty(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
void print_stack(Stack *stack);

#endif
