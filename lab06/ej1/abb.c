#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    abb left;
    abb right;
};


static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

// static bool elem_equal(abb_elem a, abb_elem b) {    /no hace falta
//     return a == b;
// }

static bool invrep(abb tree) {
    bool b = true;
    if (tree!=NULL){
        if (!abb_is_empty(tree->left)){
            b = b && elem_less(tree->left->elem, tree->elem) && invrep(tree->left);
        }
        if (!abb_is_empty(tree->right)){
            b = b && elem_less(tree->elem, tree->right->elem) && invrep(tree->right);
        }
    }
    return b;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (!abb_exists(tree, e)){
        struct _s_abb *new_branch = malloc(sizeof(struct _s_abb));
        new_branch->left = abb_empty();
        new_branch->elem = e;
        new_branch->right = abb_empty();
        if (abb_is_empty(tree)){
            tree = new_branch;
        }
        else {
            if (elem_less(e,tree->elem)){
                tree->left = abb_add(tree->left,e);
            }
            else if (elem_less(tree->elem,e)){
                tree->right = abb_add(tree->right,e);
            }
        }
    }

    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    bool b = tree==NULL;
    return b;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (!abb_is_empty(tree)){     
        if (elem_less(e,tree->elem)){
            exists = abb_exists(tree->left, e);
        }
        else if (elem_less(tree->elem,e)){
            exists = abb_exists(tree->right, e);
        }
        else{ 
            exists = true;
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        length++;
        if (!abb_is_empty(tree->left)){
            length += abb_length(tree->left);
        }
        if (!abb_is_empty(tree->right)){
            length += abb_length(tree->right);
        }        
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

static struct _s_abb* abb_find_min(struct _s_abb* tree) {
    if (tree->left == NULL) {
        return tree;
    }
    return abb_find_min(tree->left);
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (abb_is_empty(tree)) {
        return tree;  // El árbol está vacío, no hay nada que eliminar
    }

    if (elem_less(e, tree->elem)) {
        tree->left = abb_remove(tree->left, e);  // Eliminar en el subárbol izquierdo
    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_remove(tree->right, e);  // Eliminar en el subárbol derecho
    } else {
        // Caso en el que el elemento a eliminar es igual al elemento en el nodo actual

        if (abb_is_empty(tree->left) && abb_is_empty(tree->right)) {
            // Caso 1: El nodo es una hoja, simplemente lo eliminamos
            free(tree);
            tree = NULL;
        } else if (abb_is_empty(tree->left)) {
            // Caso 2: El nodo tiene solo un hijo a la derecha, reemplazamos el nodo actual por su hijo derecho
            abb right_child = tree->right;
            free(tree);
            tree = right_child;
        } else if (abb_is_empty(tree->right)) {
            // Caso 3: El nodo tiene solo un hijo a la izquierda, reemplazamos el nodo actual por su hijo izquierdo
            abb left_child = tree->left;
            free(tree);
            tree = left_child;
        } else {
            // Caso 4: El nodo tiene ambos hijos, encontramos el sucesor en orden, lo copiamos al nodo actual y lo eliminamos del subárbol derecho
            abb successor = abb_find_min(tree->right);
            tree->elem = successor->elem;
            tree->right = abb_remove(tree->right, successor->elem);
        }
    }

    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e = INT_MIN;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (abb_is_empty(tree->right)){
        max_e = tree->elem;
    }
    else{
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e = INT_MAX;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (abb_is_empty(tree->left)){
        min_e = tree->elem;
    }
    else{
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}



void abb_dump(abb tree) {
    assert(invrep(tree));

    /* ejemplo DFS pre-order */

    if (tree != NULL){
        printf("%d ",tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);   
    }        

    /* ejemplo DFS in-order */

    // if (tree != NULL) {  
    //     abb_dump(tree->left);
    //     printf("%d ", tree->elem);
    //     abb_dump(tree->right);
    //  } 
    
    /* ejemplo DFS post-order */

    // if (tree != NULL) {  
    //     abb_dump(tree->left);
    //     abb_dump(tree->right);
    //     printf("%d ", tree->elem);
    //  } 
   
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        if (!abb_is_empty(tree->left)){
            tree->left = abb_destroy(tree->left);
        }
        if (!abb_is_empty(tree->right)){
            tree->right = abb_destroy(tree->right);
        }
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

