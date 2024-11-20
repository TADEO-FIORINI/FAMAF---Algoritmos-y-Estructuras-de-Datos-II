#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    priority_t priority;
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->priority = priority;
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool b = true;
    if (s == NULL){
        b = false;
    }
    else{
        if (s->front != NULL){
            struct s_node *current = s->front;
            priority_t previous_priority = current->priority;
            while (current->next != NULL){
                current = current->next;
                priority_t current_priority = current->priority; 
                b = b && previous_priority>=current_priority;
                previous_priority = current_priority;
            }
        }
    }
    return b;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    assert(s!=NULL);
    s->size = 0;
    s->front = NULL;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    if (s->front == NULL){
        s->front = new_node;
    }
    else{
        struct s_node *current = s->front;
        struct s_node *previous = NULL;
        while (current != NULL && new_node->priority < current->priority){
            previous = current;
            current = current->next;
        }
        //la prioridad del nuevo elemento es mayor que la del primero de la pila
        if (previous == NULL){
            new_node->next = s->front;
            s->front = new_node;
        }
        //la prioridad del nuevo elemento es menor que la del ultimo de la pila
        else if (current == NULL){
            previous->next = new_node;
        }
        //caso general
        else{
            previous->next = new_node;
            new_node->next = current;
        }
    }
    s->size++;
    return s;
}

bool pstack_is_empty(pstack s) {
    bool b = s->size == 0;
    return b;
}

pstack_elem pstack_top(pstack s) {
    pstack_elem e = s->front->elem;
    return e;
}

priority_t pstack_top_priority(pstack s) {
    priority_t p = s->front->priority;
    return p;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    if (s->front != NULL){
        struct s_node *aux = s->front;
        s->front = s->front->next;
        aux = destroy_node(aux);
    }
    s->size--;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node = s->front;
    while (node != NULL) {
        struct s_node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

