#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Stack STACK;

struct Stack {
  int value;
  int is_empty;
  struct Stack *next;
};

int is_empty(STACK **stack) {
  return (*stack)->is_empty != 0;
}

int pop(STACK **stack) {
  assert(!is_empty(stack));
  STACK *copy = *stack;
  int value = (*stack)->value;
  // outer pointer (static) points to new stack now
  *stack = (*stack)->next;
  free(copy);
  return value;
}

void push(STACK **stack, int value) {
  // malloc is used so this memory can be accessed outside of scope
  STACK *head = malloc(sizeof(STACK));
  if (head) {
    head->value = value;
    // head's next is pointer to stack
    head->next = *stack;
    head->is_empty = 0;
    // stack now holds pointer to head
    *stack = head;
  } else {
    printf("push memory no alloc");
  }
}

STACK *new_stack() {
  STACK *head = malloc(sizeof(STACK));
  if (head) {
    head->value = 0;
    head->is_empty = 1;
    head->next = NULL;
    return head;
  } else {
    return NULL;
  }
}

int peek(STACK **stack) {
  STACK *head = *stack;
  return head->value;
}

int main() {
  STACK *init = new_stack();
  STACK **stack = &init;
  push(stack, 3);
  push(stack, 2);
  push(stack, 1);
  int one = pop(stack);
  printf("one: %d\n", one);
  int two = pop(stack);
  printf("two: %d\n", two);
  int three = pop(stack);
  printf("three: %d\n", three);
  //int hmm = pop(stack);
  push(stack, 5);
  printf("peek: %d", peek(stack));
  free(init);
  return 0;
}
