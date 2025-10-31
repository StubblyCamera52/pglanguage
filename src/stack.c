#include "stack.h"
#include <stdbool.h>
#include <stdio.h>

void initialize_stack(Stack *stack) { stack->top = -1; }

bool stack_empty(Stack *stack) {
  if (stack->top == -1) {
    return true;
  }
  return false;
}

void push(Stack *stack, int value) { stack->array[++stack->top] = value; }

int pop(Stack *stack) {
  int item = stack->array[stack->top--];
  return item;
}

int peek(Stack *stack) { return stack->array[stack->top]; }

void print_stack(Stack *stack) {
  printf("STACK:\n");
  for (int i = stack->top; i >= 0; i--) {
    int item = pop(stack);
    printf("%d\n", item);
  }
}
