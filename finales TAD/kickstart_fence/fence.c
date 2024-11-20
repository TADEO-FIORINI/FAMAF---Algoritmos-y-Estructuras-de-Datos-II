#include <stdlib.h>
#include <assert.h>
#include "fence.h"

struct _fence_t {
    fence_t next;
    type_t type;
};

fence_t fence_P(){
    fence_t fence = malloc(sizeof(fence_t));
    fence->type = P;
    fence->next = NULL;
    return fence;
}

fence_t fence_add_P(fence_t fence){
    assert(fence!=NULL);
    fence_t new_fence = fence_P();
    fence_t curr = fence;
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_fence;
    return fence;
}

fence_t fence_add_A(fence_t fence){
    assert(fence!=NULL);
    fence_t new_fence = fence_P();
    new_fence->type = A;
    fence_t curr = fence;
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_fence;
    return fence;
}

fence_t fence_add_H(fence_t fence){
    assert(fence!=NULL);
    fence_t new_fence = fence_P();
    new_fence->type = H;
    fence_t curr = fence;
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_fence;
    return fence;
}

fence_t fence_add_T(fence_t fence){
    assert(fence!=NULL);
    fence_t new_fence = fence_P();
    new_fence->type = T;
    fence_t curr = fence;
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_fence;
    return fence;
}

bool T_exists(fence_t fence){
    bool exists = false;
    fence_t curr = fence;
    while (curr!=NULL){
        exists |= curr->type == T;
        curr = curr->next;
    }
    return exists;
}

bool elems_between_P (fence_t fence){
    assert(fence!=NULL);
    bool betweenP = fence->type==P;
    fence_t curr = fence->next;
    if (curr!=NULL){
        while (curr->next!=NULL){
            if (curr->type!=P){
                betweenP &= curr->next->type==P;
            }
            curr = curr->next;
        }
        betweenP &= curr->type==P;
    }
    return betweenP;
}

bool fence_is_correct(fence_t fence){
    return T_exists(fence) && elems_between_P(fence);
}

unsigned int fence_perimeter(fence_t fence){
    unsigned int perimeter = 0;
    fence_t curr = fence;
    while (curr!=NULL){
        if (curr->type!=P){
            perimeter = perimeter + 3;
        }
        curr = curr->next;
    }
    return perimeter;
}

unsigned int fence_size(fence_t fence){
    unsigned int size = 0;
    fence_t curr = fence;
    while (curr!=NULL){
        size++;
        curr = curr->next;
    }
    return size;   
}

type_t *fence_to_array(fence_t fence){
    type_t *array = NULL;
    unsigned int size = fence_size(fence); 
    array = calloc(size,sizeof(type_t));
    fence_t curr = fence;
    for (unsigned int i=0; i<size; ++i){
        array[size-i-1] = curr->type;
        curr = curr->next;
    }
    return array;
}

fence_t fence_destroy(fence_t fence){
    if (fence!=NULL){
        fence_t curr = fence;
        while (curr!=NULL){
            fence_t killme = curr;
            curr = curr->next;
            free(killme);
        }
        fence = NULL;
    }
    return fence;
}
