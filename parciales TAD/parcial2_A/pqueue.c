#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct p_queue {
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next=NULL;
    free(node);
    node=NULL;
    assert(node == NULL);
    return node;
}



static bool invrep(pqueue q) {
    bool b = true;
    if (q == NULL){
        b = false;
    }
    else{
        if (q->first != NULL){
            struct s_node *current = q->first;
            unsigned int prev_priority = current->priority;
            while (current->next != NULL) {
                current = current->next;
                unsigned int current_priority = current->priority;
                b = b && prev_priority <= current_priority;
                prev_priority = current_priority;
            }
        }
    }
    return b;
}

pqueue pqueue_empty(void) {
    pqueue q=malloc(sizeof(struct p_queue));
    assert(q!=NULL);
    q->size = 0;
    q->first = NULL;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if (q->first == NULL){
        q->first = new_node;
    }
    else{
        struct s_node *current = q->first;
        struct s_node *previous = NULL;
        while (current != NULL && priority >= current->priority){
            previous = current;
            current = current->next;
        }
        //el nodo nuevo tiene mayor prioridad que el primer nodo
        if (previous == NULL){
            new_node->next = q->first;
            q->first = new_node;
        }
        //caso general
        else{
            previous->next = new_node;
            new_node->next = current;
        }
    }
    q->size++;
    return q;
}

bool pqueue_is_empty(pqueue q) {
    bool b = q->size==0;
    return b;
}

pqueue_elem pqueue_peek(pqueue q) {
    pqueue_elem e = q->first->elem;
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    unsigned int p = q->first->priority; 
    return p;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int s = q->size; 
    return s;
}

pqueue pqueue_dequeue(pqueue q) {
    if (q->first != NULL){
        struct s_node *tmp = q->first;
        q->first = q->first->next;
        free(tmp);
        q->size--;
    }
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}