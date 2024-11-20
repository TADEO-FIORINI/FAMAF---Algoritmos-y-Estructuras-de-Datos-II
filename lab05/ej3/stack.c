#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

#define INITIAL_CAPACITY 1

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool stack_invrep(stack s){
    return s != NULL;
}

stack stack_empty() {
    stack s = (stack)malloc(sizeof(struct _s_stack));
    s->elems = (stack_elem *)calloc(INITIAL_CAPACITY, sizeof(stack_elem));
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    assert(stack_invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(stack_invrep(s));
    if (s->size == s->capacity) {
        // Si la pila está llena, se solicita más memoria para el doble de la capacidad actual
        unsigned int new_capacity = s->capacity * 2;
        s->elems = (stack_elem *)realloc(s->elems, new_capacity * sizeof(stack_elem));
        s->capacity = new_capacity;
    }
    s->elems[s->size] = e;
    s->size++;
    assert(stack_invrep(s));
    return s;
}

stack stack_pop(stack s) {
    assert(stack_invrep(s));
    if (!stack_is_empty(s)) {
        s->size--;
    }
    assert(stack_invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(stack_invrep(s));
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s) {
    assert(stack_invrep(s));
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    assert(stack_invrep(s));
    stack_elem *arr = (stack_elem *)calloc(s->size, sizeof(stack_elem));
    for (unsigned int i = 0; i < s->size; i++) {
         arr[i] = s->elems[s->size - 1 - i];
    }
    assert(stack_invrep(s));
    return arr;
}

stack stack_destroy(stack s) {
    assert(stack_invrep(s));
    free(s->elems);
    free(s);
    return NULL;
}