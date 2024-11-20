/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool b = true;
    if (x->rank < y->rank){
        b = false;
    }
    return b;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int i, unsigned int j){
    player_t aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int piv, i, j;
    piv = izq;
    i = izq+1;
    j = der;
    while (i<=j){
        if (goes_before(a[i],a[piv])){
            i++;
        }
        else if (goes_before(a[piv],a[j])){
            j--;
        }
        else if (!goes_before(a[i],a[piv]) && !goes_before(a[piv],a[j])){
            swap(a, i, j);
            i++;
            j--;
        }
    }
    swap(a, piv, j);
    piv = j;
    return piv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int piv;
    if (izq<der){
        piv = partition(a,izq,der);
        if (piv != 0u){
            quick_sort_rec(a, izq, piv-1u);
        }
        quick_sort_rec(a, piv+1u, der);
    }
}


void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}




