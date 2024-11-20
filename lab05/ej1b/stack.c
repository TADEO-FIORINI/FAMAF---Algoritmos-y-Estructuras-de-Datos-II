#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define MAX_SIZE 100

struct _s_stack {
    stack_elem elems[MAX_SIZE]; // Arreglo de elementos
    int top;                    // Índice del elemento en la parte superior de la pila
};

bool stack_invrep(stack s){
    return s != NULL;
}

stack stack_empty() {
    stack s = (stack)malloc(sizeof(struct _s_stack));
    s->top = -1;  // Inicialmente la pila está vacía
    assert(stack_invrep(s));
    return s;
}

bool stack_is_empty(stack s) {
    assert(stack_invrep(s));
    return (s->top == -1);
}

bool stack_is_full(stack s) {
    assert(stack_invrep(s));
    return (s->top == MAX_SIZE - 1);
}

stack stack_push(stack s, stack_elem e) {
    assert(stack_invrep(s));
    assert(!stack_is_full(s));
    s->top++;
    s->elems[s->top] = e;
    assert(stack_invrep(s));
    return s;
}

stack stack_pop(stack s) {
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    s->top--;
    return s;
}

stack_elem stack_top(stack s) {
    assert(stack_invrep(s));
    assert(stack_is_empty(s));
    return s->elems[s->top];
}

unsigned int stack_size(stack s) {
    assert(stack_invrep(s));
    return s->top + 1;
}

stack_elem *stack_to_array(stack s) {
    assert(stack_invrep(s));
    unsigned int size = stack_size(s);
    stack_elem *arr = (stack_elem *)malloc(size * sizeof(stack_elem));
    for (unsigned int i = 0; i < size; i++) {
        arr[i] = s->elems[i];
    }
    assert(stack_invrep(s));
    return arr;
}

stack stack_destroy(stack s) {
    assert(stack_invrep(s));
    free(s);
    return NULL;
}