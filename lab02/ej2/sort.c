#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
 /* needs implementation */
    unsigned int piv;
    if (izq<der){
        piv = partition(a,izq,der);
        /*(piv == 0u) ? quick_sort_rec(a, izq, 0u) : quick_sort_rec( a, izq, piv-1u);*/
        if (piv != 0u){
            quick_sort_rec(a, izq, piv-1u);
        }
        quick_sort_rec(a, piv+1u, der);
    }
}

void quick_sort(int a[], unsigned int length) {
     quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

