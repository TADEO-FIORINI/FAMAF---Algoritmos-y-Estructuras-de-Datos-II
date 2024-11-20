#include "array_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    //your code here!!!
    FILE *file_r;
    file_r = fopen(filepath, "r"); 
    if (file_r == NULL){
        printf("error in enter file\n");
        exit(EXIT_FAILURE);     
    }
    bool res = fscanf(file_r, "%u", &max_size);
    if (res != 1){
        printf("error in enter file\n");
        exit(EXIT_FAILURE);
    }
    for ( unsigned int i=0; i<max_size; i++){
        fscanf(file_r, "%i", &array[i]);
        if (feof(file_r) != 0){
            printf("error in enter file\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file_r);
    return max_size;
    }
void array_dump(int a[], unsigned int length) {
    //your code here!!!
    printf("[");
    for (unsigned int i=0; i<length; i++){
        printf(" %i", a[i]);
    }
    printf("]\n");
}

bool array_is_sorted(int a[], unsigned int length){
    bool res;
    res = true;
    for (unsigned int i=0; i<length-1; i++){
        res = res && (a[i]<=a[i+1]);
    }
    return res;
    }