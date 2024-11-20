#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

/*
Las prioridades son los indices del arreglo dinamico. 
Cada elemento del arreglo es una estructura de nodos enlazados
*/

// valgrind --leak-check=full ./

struct s_pqueue {
    struct s_node *(*array);      // Arreglo dinamico de nodos de min_priority+1 elementos
    unsigned int size;           // Cantidad de elementos en la cola
    priority_t min_priority;    // minima prioridad (mayor indice)
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    node->next = NULL;
    free(node);
    node = NULL;
    return NULL;
}


static bool invrep(pqueue q) {
    bool b = q != NULL;
    return b;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority + 1, sizeof(struct s_node *));
    q->size = 0;
    q->min_priority = min_priority;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->array[priority] == NULL){
        q->array[priority] = new_node;
    }
    else{
        struct s_node *current = q->array[priority];
        while (current->next != NULL){
            current = current->next;
        }
        current->next = new_node; 
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    bool b = q->size == 0;
    return b;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem e;
    priority_t priority = 0;
    while (q->array[priority] == NULL){
        priority++;
    }
    e = q->array[priority]->elem;
    return e;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t priority = 0;
    while (q->array[priority] == NULL){
        priority++;
    }
    return priority;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    size_t size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t priority = 0;
    while (q->array[priority] == NULL){
        priority++;
    }
    struct s_node *killme = q->array[priority];
    q->array[priority] = q->array[priority]->next;
    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    for (priority_t priority=0; priority < q->min_priority+1; ++priority){
        if (q->array[priority] != NULL){
            struct s_node *node = q->array[priority];
            while(node != NULL){
                struct s_node *killme = node;
                node = node->next;
                killme = destroy_node(killme);
            }
        }
    }
    free(q->array);
    free(q);
    return NULL;
}
