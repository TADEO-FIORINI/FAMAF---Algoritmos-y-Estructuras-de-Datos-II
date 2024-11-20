#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"

struct _node {
   elem_t elem;
   struct _node *next;  
};

sorted_list_t sorted_list_empty()
{
   sorted_list_t list = NULL;
   return list;
}

bool invrep(sorted_list_t list){
   bool valid = true;
   if (list!=NULL){
      struct _node *curr = list;
      struct _node *prev = NULL;
      while(curr->next!=NULL){
         prev = curr;
         curr = curr->next;
         valid &= prev->elem <= curr->elem;
      }
   }
   return valid;
}

bool sorted_list_is_empty(sorted_list_t list)
{
	assert(invrep);
   return list==NULL;
}

elem_t sorted_list_head(sorted_list_t list)
{
	assert(invrep(list) && !sorted_list_empty(list));
   return list->elem;

}

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem)
{
   assert(invrep(list));
   sorted_list_t new_node = malloc(sizeof(struct _node));
   new_node->elem = elem;
   new_node->next = NULL;
   sorted_list_t curr = list;
   sorted_list_t prev = NULL;
   while(curr!=NULL && elem>=curr->elem){
      prev = curr;
      curr = curr->next;
   }
   if (prev==NULL){
      new_node->next = list;
      list = new_node;
   }
   else {
      prev->next = new_node;
      new_node->next = curr;
   }
   return list;
}

sorted_list_t sorted_list_tail(sorted_list_t list)
{
   assert(invrep(list));
   if (!sorted_list_is_empty(list)){
      sorted_list_t killme = list;
      list = list->next;
      free(killme);
   }
   return list;
}

unsigned int sorted_list_length(sorted_list_t list)
{
   assert(invrep(list));
   unsigned int length = 0;
   sorted_list_t curr = list;
   while (curr!=NULL){
      length++;
      curr = curr->next;
   }
   return length;
}

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index)
{
   assert(invrep(list) && !sorted_list_is_empty(list) && index<sorted_list_length(list));
   sorted_list_t curr = list;
   for (unsigned int i=0; i < index; ++i){
      curr = curr->next;
   }
   return curr->elem;
}

sorted_list_t list_copy (sorted_list_t list){
   sorted_list_t copy = NULL;
   sorted_list_t curr = list;
   while (curr!=NULL){
      copy = sorted_list_append(copy,curr->elem);
      curr = curr->next;
   }
   return copy;
}

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num)
{
   assert(invrep(list));
   sorted_list_t copy = NULL;
   if (num < sorted_list_length(list)){
      copy = list_copy(list);
      sorted_list_t curr = copy;
      sorted_list_t prev = NULL;
      for (unsigned int i=0; i < num; ++i){
         prev = curr;
         curr = curr->next;
      }
      sorted_list_t destroy = curr;
      prev->next = NULL;
      destroy = sorted_list_destroy(destroy);
   }
   else if (num >= sorted_list_length(list)){
      copy = list_copy(list);
   }
   return copy;
}

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num)
{
   assert(invrep(list));
   sorted_list_t copy = list_copy(list);
   if (num!=0 && num < sorted_list_length(list)){
      sorted_list_t curr = copy;
      sorted_list_t prev = NULL;
      for (unsigned int i=0; i < num; ++i){
         prev = curr;
         curr = curr->next;
      }
      sorted_list_t destroy = copy;
      prev->next = NULL;
      copy = curr;
      destroy = sorted_list_destroy(destroy);
   }
   else if (num >= sorted_list_length(list)){
      copy = sorted_list_destroy(copy);
   }
   return copy;
}

void sorted_list_print(sorted_list_t list)
{
   printf("[");
   sorted_list_t curr = list;
   while (curr!=NULL){
      printf(" %d",curr->elem);
      curr = curr->next;
   }
   printf(" ]");
}

sorted_list_t sorted_list_destroy(sorted_list_t list)
{
   assert(invrep(list));
   sorted_list_t curr = list;
   while (curr!=NULL){
      sorted_list_t killme = curr;
      curr = curr->next;
      free(killme);
      killme = NULL;
   }
   list = NULL;
   return list; 
}
