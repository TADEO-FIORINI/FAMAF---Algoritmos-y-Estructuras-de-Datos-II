
#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

typedef struct _s_stack *stack;

typedef int stack_elem;

stack stack_empty();

stack stack_push(stack s, stack_elem e);

stack stack_pop(stack s);

unsigned int stack_size(stack s);

stack_elem stack_top(stack s);

bool stack_is_empty(stack s);

stack_elem *stack_to_array(stack s);

stack stack_destroy(stack s);

bool stackinvrep(stack s);

#endif
