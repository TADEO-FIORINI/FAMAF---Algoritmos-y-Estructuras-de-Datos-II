#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tape.h"

struct _s_node {
    tape_elem elem;
    struct _s_node *next;
};

typedef struct _s_node * node_t;

struct _s_tape {
    unsigned int size;
    node_t cursor;  // Puntero al elemento actual
    node_t start;   // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
    return (tape!=NULL);
}

static node_t create_node(tape_elem e) {
    struct _s_node *node = malloc(sizeof(struct _s_node));
    node->elem = e;
    node->next = NULL;
    return node;
}

static node_t destroy_node(node_t node) {
    assert(node!=NULL);
    free(node);
    node = NULL;
    return node;
}

tape_t tape_create(void) {
    tape_t tape=NULL;
    tape = malloc(sizeof(struct _s_tape));
    tape->cursor=NULL;
    tape->start=NULL;
    tape->size=0;
    assert(invrep(tape) && tape_is_empty(tape) && tape_at_start(tape));
    return tape;
}

tape_t tape_rewind(tape_t tape) {
    tape->cursor = tape->start;
    return tape;
}


bool tape_at_start(tape_t tape) {
    bool b=false;
    b = tape->cursor == tape->start;  
    return b;
}

bool tape_at_stop(tape_t tape) {
    return(tape->cursor==NULL);
}

bool tape_is_empty(tape_t tape) {
    return ( tape->cursor==NULL&&
    tape->start==NULL&&
    tape->size==0);
}

unsigned int tape_length(tape_t tape) {
    return(tape->size);
}

tape_t tape_step(tape_t tape) {
    if (!tape_at_stop(tape)){
       tape->cursor = tape->cursor->next;
    }
    return tape;
}

tape_t tape_insertl(tape_t tape, tape_elem e) {
    //assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    node_t new_node=create_node(e);
 
    node_t current = tape->start;
    node_t prev = NULL;
    while (current!=tape->cursor){
            prev = current;
            current = current->next; 
    }
    if (prev == NULL){
        new_node->next = tape->start;
        tape->start = new_node; 
    }
    else{
        prev->next = new_node;
        new_node->next = current;                
    }
    tape->cursor = new_node;
    tape->size++;
    
    //assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_insertr(tape_t tape, tape_elem e) {
    assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
    node_t new_node=create_node(e);
    if (tape->start!= NULL) {
        new_node->next = tape->cursor->next;
        tape->cursor->next = new_node;
        tape->cursor = new_node;
    } else {
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_erase(tape_t tape) {
    assert(invrep(tape));
    if (tape->start!=NULL && !tape_at_stop(tape)){
        node_t current = tape->start;
        node_t prev = NULL;
        while (current!=tape->cursor){
                prev = current;
                current = current->next; 
        }
        node_t killme = current;
        if (prev == NULL){
            tape->start = current->next;
            tape->cursor = tape->start;  
        }
        else{
            prev->next = current->next;
            tape = tape_step(tape);
        }
        killme = destroy_node(killme);
        tape->size--;
    }
    return tape;
}


tape_elem tape_read(tape_t tape) {
    return (tape->cursor->elem);
}

void tape_dump(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    printf("#");
    while (node != NULL) {
        if (node != tape->cursor) {
            printf("-%c-", node->elem);
        } else {
            printf("-[%c]-", node->elem);
        }
        node = node->next;
    }
    if (tape->cursor==NULL) {
        printf("-[]-");
    }
    printf("#\n");
}
/*
tape_t tape_copy(tape_t tape) {
    tape_t copy = tape_create();
    copy->size = tape->size;
    if(!tape_is_empty(tape)){
        node_t current = tape->start;
        copy->cursor = NULL;
        copy = tape_insertl(copy,tape->start->elem);
        copy->cursor = copy->start;
        while(current!=NULL){
            copy = tape_insertr(copy,current->elem);
            copy = tape_step(copy);
            current = current->next;
        }
        copy->cursor = tape->cursor;
    }
    return tape;
}
*/
tape_t tape_copy(tape_t tape) {
    tape_t copy = tape_create();
    copy->size = tape->size;
    if (!tape_is_empty(tape)){
        copy->start = tape->start;
        copy->cursor = tape->start;
        node_t current = tape->start;
        while (current!=NULL){
            copy = tape_insertr(copy, current->elem);
            current=current->next;
        }
    }
    copy->cursor = tape->cursor;
    return tape;
}

tape_t tape_destroy(tape_t tape) {
    assert(tape != NULL && invrep(tape));
    node_t node = tape->start;
    while (node != NULL) {
        node_t killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(tape);
    tape = NULL;
    return tape;
}


