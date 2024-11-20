#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "list.h"

struct _list{
    list_elem elem;
    list next;
};

list empty(void){
    list l = NULL;
    return l;
}

list addl(list l, list_elem e){
    list p;
    p = malloc(sizeof(struct _list));     
    p -> elem = e;                         
    p -> next = l;                        
    l = p;                                 
    return l;                               
}

bool is_empty(list l){
    bool b = l == empty();
    return b;
}


list_elem head(list l){
    assert(!is_empty(l));
    list_elem e = l -> elem;
    return e;
}

list tail(list l){
    assert(!is_empty(l));
    list p;
    p = l;
    l = l -> next;
    free(p);
    return l;
}

unsigned int length(list l){
    unsigned int n = 0;
        list p = l;
        while(!is_empty(p)){
             n++;
             p = p -> next;
        }
    return n;
}

list concat(list l1, list l2){
    list p;
    if(!is_empty(l1)){
        p = l1;
        while(!is_empty(p -> next)){
        p = p -> next;
    }
    p -> next = l2;
    }
    else{
        l1 = l2;
    }
    return l1;
}

list_elem index(list l, unsigned int n){
    assert(length(l)>n);
    list p = l;
    for (unsigned int i=0; i<n; ++i){
        p = p -> next;
    }
    list_elem e = p -> elem;
    return e;
}

list addr(list l, list_elem e){
    list p, q;
    q = malloc(sizeof(struct _list));          
    q -> elem = e;                  
    q -> next = NULL;  
    if(!is_empty(l)){
        p = l;
        while (!is_empty(p -> next))
        {
            p = p -> next;
        }
        p -> next = q;
    }  
    else{
        l = q;
    }
    return l;
}

list take(list l, unsigned int n){
    list p = l;
    for (unsigned int i=0; i<n && !is_empty(p->next); ++i){
        p = p -> next;
    }
    p = destroy(p);
    return l;
}

list drop(list l, unsigned int n){
    list p = l;
    for (unsigned int i=0; i<n && !is_empty(p->next); ++i){
        p = l -> next;
        free(l);
        l = p;
    }
    return l;
}

list copy(list l){
    list laux, p;
    laux = empty();
    if (!is_empty(l)){
        p = l;
        while(!is_empty(p)){
            laux = addr(laux, p->elem);
            p = p -> next;
        }
    }
    return laux;
}

list destroy(list l){
    list p;
    while (!is_empty(l)){
        p = l -> next;
        free(l);
        l = p;
    }
    return l;
}