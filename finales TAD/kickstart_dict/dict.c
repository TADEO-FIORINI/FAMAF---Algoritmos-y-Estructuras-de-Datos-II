#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       

struct _s_dict {
    unsigned int size;
    struct _node_t * first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};


struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node = malloc(sizeof(struct _node_t));
    new_node->key = k;
    new_node->value = v;
    new_node->next = NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node = NULL;
    return node;
}

static bool invrep(dict_t dict) {
    bool b = false;
    if (dict!=NULL){
        b = true;
    }
    return b;
}
// --- Interface functions ---

dict_t dict_empty(void) {
    struct _s_dict *dict = NULL;
    dict = malloc(sizeof(struct _s_dict));
    dict->size = 0u;
    dict->first = NULL;
    //POS: {dict --> dict_t /\ dict_length(dict) == 0}
    assert(dict_length(dict)==0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    struct _node_t *new_node = create_node(word,def);
    if (dict_exists(dict,word)){
        struct _node_t *curr = dict->first;
        struct _node_t *prev = NULL;
        while (!key_eq(curr->key,word)){
            prev = curr;
            curr = curr->next;
        }
        assert(key_eq(word,curr->key));
        if (prev==NULL){
            new_node->next = curr->next;
            dict->first = new_node;
        }
        else{
            prev->next = new_node;
            new_node->next = curr->next;
        }
        curr = destroy_node(curr);
    }
    else{
        new_node->next = dict->first;
        dict->first = new_node;
        dict->size++;
    }
    assert(dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t def = NULL;
    if (dict_exists(dict,word)){
        struct _node_t *curr = dict->first;
        while (!key_eq(curr->key,word)){
            curr = curr->next;
        }
        def = curr->value;
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    struct _node_t *curr = dict->first;
    while (curr!=NULL){
        exists |= key_eq(curr->key,word);
        curr = curr->next;
    }
    return exists;
}
unsigned int dict_length(dict_t dict) {
    return dict->size;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (dict_exists(dict,word)){
        struct _node_t *curr = dict->first;
        struct _node_t *prev = NULL;
        while (!key_eq(curr->key,word)){
            prev = curr;
            curr = curr->next;
        }
        struct _node_t *killme = curr;
        if (prev==NULL){
            dict->first = curr->next;
        }
        else{
            prev->next = curr->next;
        }
        killme = destroy_node(killme);
        dict->size--;
    }
    assert(!dict_exists(dict,word));
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}
/*
dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    struct _node_t *curr = dict->first;
    while (curr!=NULL){
        dict->first = dict->first->next;
        curr = destroy_node(curr);
        curr = dict->first;
        dict->size--;
    }
    assert(dict->size==0 && dict->first==NULL);
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}
*/

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    dict = dict_destroy(dict);
    dict = dict_empty();
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    struct _node_t *curr = dict->first;
    struct _node_t *prev = NULL;
    while (curr!=NULL){
        prev = curr;
        curr = curr->next;
        prev = destroy_node(prev);
        dict->size--;
    }
    free(dict);
    dict = NULL;
    return dict;
}