#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"


//¿Funciona bien stack_pop() para pilas de tamaño 1?
//Si la pila queda vacía, ¿puedo volver a insertar elementos?

void stack_check(){
    stack s = stack_empty();
    s = stack_push(s, 2);
    s = stack_pop(s);
    assert(stack_is_empty(s));
    s = stack_push(s, 4);
    assert(stack_top(s) == 4);
}

//¿La función stack_to_array() devuelve NULL para una pila vacía? 
//¿Devuelve los elementos en el orden correcto?

void stack_to_array_check(){
    stack s = stack_empty();
    stack_elem *array = NULL;
    array = stack_to_array(s);
    assert(array == NULL);
    s = stack_push(s,2);
    s = stack_push(s,4);
    s = stack_push(s,8);
    array = stack_to_array(s);
    assert(array[0]==2);
    assert(array[1]==4);
    assert(array[2]==8);
}