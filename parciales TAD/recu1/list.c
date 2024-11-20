#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct _list
{
    struct _node* head;
    ListSize size;
};

struct _node
{
    elem e;
    struct _node* next;
};

/**
 * @brief Invariante de represetación
 *
 * @param l Lista
 * @return true Si l es una lista válida
 * @return false Si l NO es una lista válida
 */
static bool invrep(list l)
{
    return l != NULL;
}

/**
 * @brief Crea un nodo de la lista nuevo
 *
 * @param e Elemento que contendrá el nodo
 * @return struct _node* Nuevo nodo creado o NULL si no hay memoria
 */
static struct _node* create_node(elem e)
{
    struct _node* res = malloc(sizeof(struct _node));
    if (res != NULL)
    {
        res->e = e;
        res->next = NULL;
    }
    return res;
}

/**
 * @brief Destruye el nodo node
 *
 * @param node Nodo a ser destruido
 * @return struct _node* Devuelve NULL si el nodo se destruyó correctamente
 */
static struct _node* destroy_node(struct _node* node)
{
    if (node != NULL)
    {
        free(node);
        node = NULL;
    }
    assert(node == NULL);
    return node;
}

list list_empty()
{
    list res = NULL;
    res = malloc(sizeof(struct _list));
    res->head = NULL;
    res->size = 0;
    assert(invrep(res));
    return res;
}

list list_addl(list l, elem e)
{
    assert(invrep(l));
    struct _node *new_node = create_node(e);
    if (list_is_empty(l)){
        l->head = new_node;
    }
    else{
        new_node->next = l->head;
        l->head = new_node;
    }
    l->size++;
    assert(invrep(l));
    return l;
}

list list_addr(list l, elem e)
{
    assert(invrep(l));
    struct _node *new_node = create_node(e);
    if (list_is_empty(l)){
        l->head = new_node;
    }
    else{
        struct _node *current = l->head;
        struct _node *prev = NULL;
        while (current!=NULL){
            prev = current;
            current = current->next;
        }
        prev->next = new_node;
    }
    l->size++;
    assert(invrep(l));
    return l;
}

bool list_is_empty(list l)
{
    assert(l != NULL && invrep(l));
    return (l->head == NULL && l->size == 0);  
}

elem list_head(list l)
{
    assert(l != NULL && invrep(l) && !list_is_empty(l));
    elem e = l->head->e;
    return e;  
}

list list_tail(list l)
{
    assert(!list_is_empty(l));
    struct _node *aux = l->head;
    l->head = l->head->next;
    destroy_node(aux);
    l->size--;
    return l;
}

ListSize list_length(list l)
{
    assert(l != NULL);
    return (l->size);
}

void list_print(list l)
{   printf("[");
    struct _node *current = l->head;
    while (current!=NULL){
        printf(" %u",current->e);
        current = current->next;
    }
    printf(" ]");
}

list list_destroy(list l)
{
    assert(l != NULL && invrep(l));
    struct _node *node = l->head;
    while (node != NULL) {
        struct _node *killme = node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(l);
    l = NULL;
    return l;
}

/* Funciones Anexas */

list list_greater_than(list l, unsigned int n)
{
    assert(invrep(l));
    list lgt = list_empty();
    if (!list_is_empty(l)){
        struct _node *current = l->head;
        while (current!=NULL){
            if (current->e > n){
                lgt = list_addr(lgt,current->e);
            }
            current = current->next;
        }
    }
    return lgt;
}

unsigned int list_greater_than_count(list l, unsigned int n)
{
    list lgt = list_greater_than(l,n);
    unsigned int longitud = list_length(lgt);
    lgt = list_destroy(lgt);
    return longitud;
}


list list_insert_at(list l, unsigned int position, elem e)
{
    assert(l != NULL && invrep(l));
    if (position <= l->size){
        if (position == 0){
            l = list_addl(l,e);
        }
        else if (position == l->size-1){
            l = list_addr(l,e);
        }
        else{
            struct _node *new_node = create_node(e);
            struct _node *current = l->head;
            struct _node *prev = NULL;
            for (unsigned int i=0; i<position; ++i){
                prev = current;
                current = current->next;
            }
            prev->next = new_node;
            new_node->next = current;
            l->size++;
        }
    }
    return l;
}
