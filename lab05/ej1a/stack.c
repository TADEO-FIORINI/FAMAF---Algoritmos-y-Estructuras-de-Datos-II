#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;    // Elemento de la pila
    stack next;         // Puntero al siguiente nodo de la pila
};

bool stack_invrep(stack s){
    return s != NULL;
}

stack stack_empty() {
    stack s = (stack)malloc(sizeof(struct _s_stack));
    s -> elem = 0;
    s -> next = NULL;
    assert(stack_invrep(s));
    return s;
}


stack stack_push(stack s, stack_elem e) {
    assert(stack_invrep(s));
    stack new_node = (stack)malloc(sizeof(struct _s_stack));
    new_node->elem = e;
    new_node->next = s;
    assert(stack_invrep(s));
    return new_node;
}

stack stack_pop(stack s) {
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    stack next_node = s->next;
    free(s);
    assert(stack_invrep(next_node));
    return next_node;
}

unsigned int stack_size(stack s) {
    assert(stack_invrep(s));
    unsigned int size = 0;
    stack current = s;
    while (!stack_is_empty(current)) {
        size++;
        current = current->next;
    }
    assert(stack_invrep(s));
    return size;
}

stack_elem stack_top(stack s) {
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s) {
    assert(stack_invrep(s));
    return (s->elem == 0 && s->next == NULL);
}

stack_elem *stack_to_array(stack s) {
    assert(stack_invrep(s));
    unsigned int size = stack_size(s);
    stack_elem *arr = (stack_elem *)calloc(size, sizeof(stack_elem));
    stack current = s;
    for (unsigned int i = 0; i < size; i++) {
        arr[size -1 -i] = current->elem;
        current = current->next;
    }
    assert(stack_invrep(s));
    return arr;
}

stack stack_destroy(stack s) {
    assert(stack_invrep(s));
    while (!stack_is_empty(s)) {
        stack next_node = s->next;
        free(s);
        s = next_node;
    }
    return NULL;
}