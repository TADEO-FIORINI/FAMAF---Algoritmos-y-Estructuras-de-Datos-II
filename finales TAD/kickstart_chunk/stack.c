#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem chunk[CHUNK_CAPACITY];
    unsigned int used;
    struct s_node *next;
};

struct _s_stack {
    unsigned int size;
    struct s_node *top;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    while (check!=NULL) {
        if (check==s->top){
            valid = check->used <= CHUNK_CAPACITY;
        }
        else{
            valid &= check->used == CHUNK_CAPACITY;
        }
        check = check->next;
    }
    return valid;
}


bool check_size(stack s){
    unsigned int size = 0;
    struct s_node *check = s->top;
    while (check!=NULL){
        size += check->used;
        check = check->next;
    }
    return (s!=NULL && valid_chunks(s) && size==s->size);
}    

static bool
invrep(stack s) {
    return check_size(s) && valid_chunks(s);
}


static struct s_node *
create_node(void) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    new_node->used = 0;
    new_node->next = NULL; 
    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) {
    stack s = malloc(sizeof(struct _s_stack));
    s->size = 0;
    s->top = NULL;
    return s;
}


stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if (stack_is_empty(s)){
        struct s_node *new_node = create_node();
        new_node->chunk[new_node->used] = e;
        new_node->used++;
        s->top = new_node;
    }
    else{
        if (s->top->used < CHUNK_CAPACITY){
            s->top->chunk[s->top->used] = e;
            s->top->used++;
        }
        else if (s->top->used==CHUNK_CAPACITY){
            struct s_node *new_node = create_node();
            new_node->chunk[new_node->used] = e;
            new_node->used++;
            new_node->next = s->top;
            s->top = new_node;
        }   
    }
    s->size++;
    return s;
}


stack stack_pop(stack s) {
    assert(invrep(s));
    if (!stack_is_empty(s)){
        if (s->top->used > 1){
            s->top->used--;
        }
        else if (s->top->used==1){
            struct s_node *killme = s->top;
            s->top = s->top->next;
            killme = destroy_node(killme);
        }
        s->size--;
    }
    return s;
}



unsigned int stack_size(stack s) {
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    if (!stack_is_empty(s)){
        *top = s->top->chunk[s->top->used-1];
    }
}

bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->top==NULL && s->size==0;
}

stack_elem *stack_to_array(stack s) { 
    assert(invrep(s));
    stack_elem *array = NULL;
    if (!stack_is_empty(s)){
        unsigned int size = stack_size(s);
        array = calloc(size,sizeof(stack_elem));
        struct s_node *curr = s->top;
        unsigned int j = 0;
        while (curr!=NULL){
            for (unsigned int i=0; i < curr->used; ++i){
                array[j+i] = curr->chunk[i];
            }
            j += curr->used;
            curr = curr->next;
        }
    }
    return array;
}


stack stack_destroy(stack s) {
    assert(invrep(s));
    struct s_node *curr = s->top;
    while (curr!=NULL){
        struct s_node *killme = curr;
        curr = curr->next;
        free(killme);
        killme = NULL;
    }
    free(s);
    s = NULL;
    return s;
}