#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s0_node *(*array);
    size_t size;
    priority_t max_priority; //mayor prioridad (y mayor indice)
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node!=NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    bool b = s != NULL;
    return b;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->array = calloc(max_priority+1, sizeof(struct s_node *));
    s->max_priority = max_priority;
    s->size = 0;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e);
    new_node->next = s->array[priority];
    s->array[priority] = new_node;
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    bool b = s->size == 0;
    return b;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t priority = s->max_priority;
    while (s->array[priority] == NULL){
        priority--;
    }
    pstack_elem top = s->array[priority]->elem;
    return top;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t priority = s->max_priority;
    while (s->array[priority] == NULL){
        priority--;
    }
    return priority;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    size_t size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t priority = pstack_top_priority(s);
    struct s_node *killme = s->array[priority];
    s->array[priority] = s->array[priority]->next;
    killme = destroy_node(killme);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    for (priority_t i=0; i < s->max_priority+1; ++i){
        if (s->array[i] != NULL)
        {
            struct s_node *node = s->array[i];
            while (node != NULL)
            {
                struct s_node *killme = node;
                node = node->next;
                killme = destroy_node(killme);
            }        
        }
    }
    free(s->array);
    free(s);
    s = NULL;
    return s;
}