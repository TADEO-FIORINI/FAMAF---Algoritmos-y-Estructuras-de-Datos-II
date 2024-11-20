#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

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
La diferencia entre la especificación del enunciado y la que vemos en pair.h es que
aquella habla de un par de tipo T, mientra que esta declara un par de tipo Int
*/