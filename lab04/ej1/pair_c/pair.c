#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */
#include <assert.h>

typedef struct s_pair_t * pair_t;

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t p;
    p = malloc(sizeof(p));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
    assert(p!=NULL);
    int x;
    x = p->fst;
    return x;
}

int pair_second(pair_t p){
    assert(p!=NULL);
    int y;
    y = p->snd;
    return y;
}

pair_t pair_swapped(pair_t p){
    assert(p!=NULL);
    int x;
    x = p->fst;
    p->fst = p->snd;
    p->snd = x; 
    return p;
}

pair_t pair_destroy(pair_t p){
    p = NULL;
    free(p);
    return p;
}

/*
La implementacion logra encapsulamiento ya que a partir de la especificación
implementamos el TAD de una forma asi como tambien lo podriamos haber hecho
de otra.  
*/