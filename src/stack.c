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

void push(Stack *stack, StackItem value) { stack->array[++stack->top] = value; }

StackItem pop(Stack *stack) {
  StackItem item = stack->array[stack->top--];
  return item;
}

StackItem peek(Stack *stack) { return stack->array[stack->top]; }

void print_stack(Stack *stack) {
  printf("STACK:\n");
  for (int i = stack->top; i >= 0; i--) {
    StackItem item = pop(stack);

    switch (item.type) {
    case LITERAL: {
      printf("%d\n", item.literal.value);
      break;
    }
    case IDENT: {
      printf("%s\n", item.ident.name);
      break;
    }
    default: {
        printf("block");
        break;
    }
    }
  }
}

StackItem st_from_int(int value) {
    StackItem item;
    item.type = LITERAL;
    item.literal.value = value;

    return item;
}
