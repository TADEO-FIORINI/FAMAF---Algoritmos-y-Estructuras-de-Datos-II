#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void insert(int a[], unsigned int i) {
    unsigned int j;
    j = i;
    while (j>0 && !goes_before(a[j-1], a[j])){
        swap(a, j, j-1);       
        j--;      
    }      
    }

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1; i < length; ++i) {
        insert(a, i);   
        for (unsigned int j=0; j!=i; j++){
            assert(array_is_sorted(a,j));
        }
    }
}

/*
La funcion goes_before toma dos variables de tipo int y verifica si la primera es menor o igual que la segunda en terminos de valor absoluto
*/

