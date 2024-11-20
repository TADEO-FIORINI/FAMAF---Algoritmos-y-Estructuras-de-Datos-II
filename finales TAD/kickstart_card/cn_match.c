#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cn_match.h"
#include "card.h"

struct _s_match {
  card c;
  unsigned int size;
  struct _s_match *next; 
};

cn_match match_new(void) {
  struct _s_match *new_match = NULL;
  new_match = malloc(sizeof(struct _s_match));
  new_match->c = NULL;
  new_match->size = 0;
  new_match->next = NULL;
  return new_match;
}

cn_match match_add(cn_match match, card c) {
  if (match!=NULL){
    if (match->c==NULL && match->next==NULL){
      match->c = c;
    }
    else if (match->c!=NULL){
      struct _s_match *new_match = match_new();
      new_match->c = c;
      new_match->next = NULL;
      struct _s_match *current = match;
      while (current->next!=NULL){
        current = current->next;
      }
      current->next = new_match;
    }
  }
  match->size++;
  return match;
}

unsigned int match_size(cn_match match) {
  unsigned int cards = match->size;
  return cards;
}

bool check_pair_cards(cn_match match) {
  return match_size(match)%2==0;
}

bool check_hand(card fst_player_card, card snd_player_card){
  return card_player(fst_player_card)==1 && card_player(snd_player_card)==2;
}

unsigned int match_length(cn_match match) {
  unsigned int hands = 0;
  if (is_match_correct(match)){
    hands = match_size(match)/2;
  }
  return hands;
}

bool is_match_correct(cn_match match) {
  bool b = false;
  if (check_pair_cards(match)){
    struct _s_match *current = match;
    struct _s_match *prev = NULL;
    b = true;
    while (current!=NULL && current->next!=NULL){
      prev = current;
      current = current->next;
      struct _s_match *fst_player = prev;
      struct _s_match *snd_player = current;
      b = b && check_hand(fst_player->c,snd_player->c);
      current = current->next;
    }
  }
  return b;
}
unsigned int winner_total_points(cn_match match) {
  unsigned int max_points = 0;
  if (is_match_correct(match)){
    unsigned int points_fst_player = 0;
    unsigned int points_snd_player = 0;
    struct _s_match *current = match;
    struct _s_match *prev = NULL;
    while (current!=NULL && current->next!=NULL){
      prev = current;
      current = current->next;
      struct _s_match *fst_player = prev;
      struct _s_match *snd_player = current;
      points_fst_player += card_pair_points(fst_player->c,snd_player->c,1);
      points_snd_player += card_pair_points(fst_player->c,snd_player->c,2); 
      current = current->next;
    }    
    if (points_fst_player<points_snd_player){
      max_points = points_snd_player;
    }
    else{
      max_points = points_fst_player;
    }
  }
  return max_points;
}

card * match_to_array(cn_match match) {
    card *array = NULL;
    unsigned int size = match_size(match);
    if (size!=0){
        array = calloc(size,sizeof(card));
        struct _s_match *current = match;
        for (unsigned int i=0; i<size; ++i){
            array[i] = current->c;
            current = current->next;
        }
    }
    return array;
}

void match_dump(cn_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

cn_match match_destroy(cn_match match) {
    struct _s_match *current = match;
    while (current!=NULL){
        struct _s_match *killme = current;
        current = current->next;
        killme->c = card_destroy(killme->c);
        free(killme);

    }
    match = NULL;
    return match;
}
