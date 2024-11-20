#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"


struct s_set {
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

static bool
invrep(set s) {
    bool b = true;
    if (s==NULL){
        b = false;
    }
    else{
        if (s->first != NULL){
            node_t current = s->first;
            set_elem e = current->elem;
            while (current->next != NULL){
                current = current->next;
                b = b && e < current->elem;

            }
        }
    }
    return b;
}

static struct s_node *create_node(set_elem e){
    node_t new_node = malloc(sizeof(node_t));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(node_t node){
    if (node != NULL){
        node->next = NULL;
        free(node);
        node = NULL;
        assert(node==NULL);
    }
   return node;
}


/* CONSTRUCTORS */

set set_empty(void) {
    struct s_set *s = malloc(sizeof(struct s_set));
    s->first = NULL;
    s->size = 0;
    assert(invrep(s));
    return s;
}

set set_add(set s, set_elem e) {
    assert(invrep(s));    
    unsigned int size = s->size;
    node_t new_node = create_node(e);
    if (set_is_empty(s)){
        s->first = new_node;
        s->size++;
    }
    else {
        node_t current = s->first;
        node_t previous = NULL;
        while (current != NULL && e > current->elem){  //  1 3 4 
            previous = current;
            current = current->next;
            
        }
        // el nuevo elemento es el mas pequeño del set
        if (previous == NULL && e < current->elem){
                new_node->next = s->first;
                s->first = new_node;
                s->size++;
        }   
        // el nuevo elemento es el mas grande del set      
        else if (current == NULL){
            previous->next = new_node;
            s->size++;
        }  
        //caso general
        else if (e < current->elem){
            previous->next = new_node;
            new_node->next = current;
            s->size++;
        }
    }
    //vemos si el elemento se agrego 
    unsigned int new_size = s->size;
    if (size == new_size){
        new_node = destroy_node(new_node);
    }
    assert(invrep(s));
    return s;    
    }

/* OPERATIONS   */
unsigned int set_cardinal(set s) {
    unsigned int size = s->size;
    return size;
}

bool set_is_empty(set s) {
    bool b = s->size == 0 && s->first == NULL;
    return b;
}

bool set_member(set_elem e, set s) {
    assert(invrep(s));
    struct s_node *node = s->first;
    while (node!=NULL && node->elem < e) {
        node = node->next;
    }
    return (node!=NULL && node->elem==e);
}


set set_elim(set s, set_elem e) {
    assert(invrep(s) && !set_is_empty(s));
    if (set_member(e,s)){
        node_t current = s->first;
        node_t previous = NULL;
        while (current != NULL && current->elem < e){
            previous = current;
            current = current->next;
        }
        node_t killme = current;
        current = current->next;
        previous->next = current;
        killme = destroy_node(killme);
        s->size--;
    }
    return s;
}

set_elem set_get(set s) {
    set_elem e = s->first->elem;
    return e;
}

set_elem *set_to_array(set s) {
    assert(invrep(s));
    set_elem *array = NULL;
    if (!set_is_empty(s)){
        array = calloc(s->size,sizeof(set_elem));
        node_t current = s->first;
        for (unsigned int i=0; i<s->size; ++i){
            array[i] = current->elem;
            current = current->next;
        }
    }
    return array;
}

set set_destroy(set s) {
    assert(invrep(s));
    node_t node = s->first;
    
    while (node != NULL){
        node_t killme = node;
        node = node->next;
        killme = destroy_node(killme);
       
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
