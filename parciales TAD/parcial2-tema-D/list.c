#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

// valgrind --leak-check=full ./

struct _node_t {
  unsigned int key;
  list_value value;
  struct _node_t *next;
};

typedef struct _node_t * node_t;

struct _list_t {
  unsigned int size;
  node_t elems;
};

static bool invrep(list_t list) {
  bool b = true;
  if (list==NULL){
      b = false;
  }
  else{
      if (list->elems != NULL){
          node_t current = list->elems;
          unsigned int k = current->key;
          while (current->next != NULL){
              current = current->next;
              b = b && k < current->key;
          }
      }
  }
  return b;
}

static struct _node_t * create_node(unsigned int key, list_value value) {
    node_t new_node = malloc(sizeof(node_t));
    assert(new_node!=NULL);
    new_node->value = value;
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

static struct _node_t * destroy_node(struct _node_t *node) {
  while (node != NULL){
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
  }
  return node;
}

list_t list_empty(void) {
  list_t list = malloc(sizeof(struct _list_t));
  list->elems = NULL;
  list->size = 0;
  assert(invrep(list)); 
  return list;
}

list_t list_add(list_t list, unsigned int key, list_value value) {
  assert(invrep(list));
  if (list_is_empty(list)){
    // diccionario vacio
    node_t new_node = create_node(key,value);
    list->elems = new_node;
    list->size++;
  }
  else{
    // si la clave ya existe la busco, sino busco la ultima clave que cumpla la invariante
    node_t current = list->elems;
    node_t previous = NULL;
    while (current != NULL && current->key < key){
      previous = current;
      current = current->next;
    }
    if (!list_exists(list,key)){
      // no existe ningun dato con la nueva clave
      node_t new_node = create_node(key,value);
      if (previous == NULL){
        new_node->next = list->elems;
        list->elems = new_node;
      }
      else if (current == NULL){
        previous->next = new_node;
      }
      else{
        previous->next = new_node;
        new_node->next = current;
      }
      list->size++;
    }
    else{
      // ya existe un dato con la nueva clave
      current->value = value;
    }
  }
  return list;
}

unsigned int list_length(list_t list) {
  assert(invrep(list));
  return (list->size);
}

bool list_is_empty(list_t list) {
  assert(invrep(list));
  return (list->size == 0 && list->elems == NULL);
}

bool list_exists(list_t list, unsigned int key) {
  assert(invrep(list));
  node_t cursor = list->elems;
  while (cursor != NULL && cursor->key < key) {
    cursor = cursor->next;
  }
  return cursor != NULL && cursor->key == key;
}


char list_search(list_t list, unsigned int key) {
  assert(invrep(list));
  assert(list_exists(list,key));
  node_t current = list->elems;
  // buscamos la clave
  while (current->key < key){
    current = current->next;
  }
  return (current->value);
}

list_t list_remove(list_t list, unsigned int key) {
  assert(invrep(list));
  if(list_exists(list,key)){
    node_t current = list->elems;
    node_t previous = NULL;
    // buscamos la clave
    while (current->key < key){
      previous = current;
      current = current->next;
    }
    node_t killme = current;
    current = current->next;
    if (previous != NULL){ 
      previous->next = current;
    }
    killme = destroy_node(killme);
    list->size--;
  }
  return list; 
}

list_t list_remove_all(list_t list) {
  assert(invrep(list));
  if (!list_is_empty(list)){
    node_t node = list->elems;
    node_t killme = node;
    while (node != NULL){
      node = node->next;
      killme = destroy_node(killme);
      killme = node;
      list->size--;
    }
  }
  return list;
}


list_value* list_to_array(list_t list) {
    assert(invrep(list));
    list_value *array = NULL;
    if (!list_is_empty(list)){
        array = calloc(list->size,sizeof(list_value));
        node_t current = list->elems;
        for (unsigned int i=0; i < list->size; ++i){
            array[i] = current->value;
            current = current->next;
        }
    }
    return array;
}

list_t list_destroy(list_t list) {
  assert(invrep(list));
  list = list_remove_all(list);
  free(list);
  list = NULL;
  return list;
}
