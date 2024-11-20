#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    domino tile;
    struct _s_line *next;
};

domino_line line_new(domino first) {
    //assert(domino_is_double(first));
    struct _s_line *new_line = malloc(sizeof(struct _s_line));
    new_line->tile = first;
    new_line->next = NULL;
    return new_line;
}

domino_line line_add(domino_line line, domino t) {
    struct _s_line *curr = line;
    struct _s_line *new_line = line_new(t);
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_line;
    return line;
}

unsigned int line_length(domino_line line) {
    unsigned int length = 0;
    struct _s_line *curr = line;
    while(curr!=NULL){
        length++;
        curr = curr->next;
    }
    assert(length>0);
    return length;
}

bool line_n_correct(domino_line line, unsigned int n) {
    assert(n<line_length(line));
    bool line_is_correct = true;
    unsigned int length = line_length(line);
    if (length>1){
        struct _s_line *curr = line;
        struct _s_line *prev = NULL;
        unsigned int i = 0;
        while (i<n){
            prev = curr;
            curr = curr->next;
            i++;
        }
        if (i==0){
            prev = curr;
            curr = curr->next;
            line_is_correct = domino_matches(prev->tile,curr->tile);
        }
        else if (0<i && i<length-1){
            line_is_correct = domino_matches(prev->tile,curr->tile);
            prev = curr;
            curr = curr->next;
            line_is_correct &= domino_matches(prev->tile,curr->tile);
        }
        else if (i==length-1){
            line_is_correct = domino_matches(prev->tile,curr->tile);
        }
    }
    return line_is_correct;
}

int line_total_points(domino_line line) {
    struct _s_line *curr = line;
    int total_points = 0;
    while (curr!=NULL){
        total_points += domino_up(curr->tile) + domino_down(curr->tile);
        curr = curr->next;
    }
    return total_points;
}

domino * line_to_array(domino_line line) {
    unsigned int size = line_length(line);
    domino *array = calloc(size,sizeof(domino));
    struct _s_line *curr = line;
    for (unsigned int i=0; i<size; ++i){
        array[i] = curr->tile;
        curr = curr->next;
    }
    return array;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    struct _s_line *curr = line;
    while (curr!=NULL){
        struct _s_line *killme = curr;
        curr = curr->next;
        killme->tile = domino_destroy(killme->tile);
        free(killme);
    }
    line = NULL;
    return line;
}

