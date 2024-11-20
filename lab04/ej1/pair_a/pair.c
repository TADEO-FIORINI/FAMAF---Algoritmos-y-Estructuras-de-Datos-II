#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

pair_t pair_new(int x, int y){
    pair_t p;
    p.fst = x;
    p.snd = y;
    return p;
}

int pair_first(pair_t p){
    int x;
    x = p.fst;
    return x;
}

int pair_second(pair_t p){
    int y;
    y = p.snd;
    return y;
}

pair_t pair_swapped(pair_t p){
    int x;
    x = p.fst;
    p.fst = p.snd;
    p.snd = x; 
    return p;
}

pair_t pair_destroy(pair_t p){
    return p;
}

/*
La implementacion NO logra encapsulamiento ya que la especificacion nos está
diciendo explicitamente como tenemos que impletar el TAD (una estructura de dos enteros)
*/