#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool b;
    if (d==NULL){
        b = false;
    }
    else{
        b = true;
        if (d->left != NULL){
            b = b && key_less(d->left->key, d->key) && invrep(d->left);
        }
        if (d->right != NULL){
            b = b && key_less(d->key, d->right->key) && invrep(d->right);
        }        
    }
    return true;
}

dict_t dict_empty(void) {
    dict_t dict = malloc(sizeof(struct _node_t));
    dict->left = NULL;
    dict->right = NULL;
    dict->key = NULL;
    dict->value = NULL;
    return dict;
}

bool dict_is_empty(dict_t dict){
    assert(invrep(dict));
    return (dict->left == NULL &&
    dict->right == NULL &&
    dict->key == NULL &&
    dict->value == NULL);
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict_is_empty(dict)){
        dict->key = word;
        dict->value = def;
    }
    else{
        if (key_eq(dict->key,word)){
            dict_t new_dict = dict_empty();
            new_dict->left = dict->left;
            new_dict->right = dict->right;
            new_dict->key = word;
            new_dict->value = def;
            dict->value = value_destroy(dict->value); 
            dict->key = key_destroy(dict->key);
            free(dict);
            dict = new_dict;            
        }
        else{
            if (key_less(word,dict->key)){
                if (dict->left==NULL){
                    dict->left = dict_empty();
                    dict->left = dict_add(dict->left,word,def);
                }   
            }                  
            if (key_less(dict->key,word)){
                if (dict->right==NULL){
                    dict->right = dict_empty();
                }
                dict->right = dict_add(dict->right,word,def);
            }            
        }
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    if (dict_exists(dict,word)){
        if (key_less(word,dict->key)){
            def = dict_search(dict->left,word);
        }
        else if (key_less(dict->key,word)){
            def = dict_search(dict->right,word);
        }
        else{
            def = dict->value;
        }     
    }
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool b=false;
    if (!dict_is_empty(dict)){
        if (dict->left!=NULL){
            if (key_less(word,dict->key)){
                b = dict_exists(dict->left,word);
            }
        } 
        if (dict->right!=NULL){
            if (key_less(dict->key,word)){
                b = dict_exists(dict->right,word);
            }
        }
        if (key_eq(dict->key,word)){
            b = true;
        }
    }     
    return b;

}
unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = 0u;
    if (!dict_is_empty(dict)){
        length++;
        if (dict->left!=NULL){
            length += dict_length(dict->left);
        }
        if (dict->right!=NULL){
            length += dict_length(dict->right);
        }        
    }
    return length;
}

dict_t dict_find_min(dict_t dict) {
    if (dict_is_empty(dict)) {
        dict_find_min(dict->left);
    }
    return dict;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (!dict_is_empty(dict)) {  
        if (dict->left!=NULL){
            if (key_less(word, dict->key)) {
                dict->left = dict_remove(dict->left, word);
            }
        }
        if (dict->right!=NULL){
            if (key_less(dict->key, word)) {
                dict->right = dict_remove(dict->right, word);
            }
        }    
        if (key_eq(dict->key,word)) {
            if (dict->left==NULL && dict->right==NULL) {
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = NULL;
            } else if (dict->left==NULL) {
                dict_t right_child = dict->right;
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = right_child;
            } else if (dict->right==NULL) {
                dict_t left_child = dict->left;
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = left_child;
            } else {
                dict_t successor = dict_find_min(dict->right);
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                dict->key = successor->key;
                dict->value = successor->value;
                dict->right = dict_remove(dict->right, successor->key);
            }
        }
    }
    return dict;   
}
   

dict_t dict_remove_all(dict_t dict) {
    dict = dict_destroy(dict);
    dict = dict_empty();
    return dict;
}

void key_value_dump(dict_t dict, FILE *file){
    key_dump(dict->key, file);
    fprintf(file,": ");
    value_dump(dict->value, file);
    fprintf(file, "\n");
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (!dict_is_empty(dict)){
        // DFS in-order
        if (dict->left!=NULL){
            dict_dump(dict->left, file);
        }
        key_value_dump(dict, file);
        if (dict->right!=NULL){
            dict_dump(dict->right, file);
        } 
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if (dict!=NULL){
        if (dict->left!=NULL){
            dict->left = dict_destroy(dict->left);
        }
        if (dict->right!=NULL){
            dict->right = dict_destroy(dict->right);
        }
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict=NULL;
    }
    return dict;
}