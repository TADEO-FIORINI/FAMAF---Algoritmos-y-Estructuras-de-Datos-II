
/*
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool stack_invrep(stack s){
    bool b = s != NULL;
    return b;
}

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = NULL;
    s->size = 0;
    s->capacity = 0;
    assert(stack_invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(stack_invrep(s));
    //duplicar capacidad del arreglo
    if (s->size == s->capacity){
        unsigned int new_capacity = 2*s->capacity;
        if (new_capacity == 0){
            s->elems = (stack_elem*) calloc(1, sizeof(stack_elem));
        }
        s->elems = (stack_elem*) realloc(s->elems, new_capacity * sizeof(stack_elem));
        s->capacity = new_capacity;
    }
    //agregar elemento
    s->elems[s->size] = e;
    s->size++;
    assert(stack_invrep(s));
    return s;
}

stack_elem stack_top(stack s){
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    s->size--;
    stack_elem e = s->elems[s->size];
    assert(stack_invrep(s));
    return e;
}

stack stack_pop(stack s){
    assert(stack_invrep(s));
    assert(!stack_is_empty(s));
    s->size--;
    assert(stack_invrep(s));
    return s;
}

bool stack_is_empty(stack s){
    assert(stack_invrep(s));
    bool b = s->size == 0; 
    assert(stack_invrep(s));
    return b;
}

unsigned int stack_size(stack s){
    assert(stack_invrep(s));
    unsigned int size = s->size;
    assert(stack_invrep(s));
    return size;
}

stack_elem *stack_to_array(stack s){
    assert(stack_invrep(s));
    unsigned int size = s->size;
    stack_elem *array = calloc(size,sizeof(stack_elem));
    for (unsigned int i=size; i>0; --i){
        array[i-1] = s->elems[i-1];
    }
    assert(stack_invrep(s));
    return array;
}
*/
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
         arr[i] = s->elems[i];
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