#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "war_match.h"
#include "card.h"

struct _s_match {
  card card;
  war_match next;
};

war_match match_new(void) {
  war_match new_match = malloc(sizeof(war_match));
  new_match->card = NULL;
  new_match->next = NULL;
  return new_match;
}

war_match match_add(war_match match, card c) {
  assert(match!=NULL);
  if (match->card==NULL){
    match->card = c;
  }
  else{
    war_match new_match = match_new();
    new_match->card = c;
    war_match curr = match;
    while (curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_match;
  }
  return match;
}

unsigned int match_size(war_match match) {
  unsigned int size = 0;
  if (match->card!=NULL){
    war_match curr = match;
    while (curr!=NULL){
        size++;
        curr = curr->next;
    }
  }
  return size;
}

unsigned int match_length(war_match match) {
    unsigned int length = 0;
    if (is_match_correct(match)){
        length = match_size(match)/2;
    }
    return length;
}

bool is_match_correct(war_match match) {
    bool correct_match = false;
    unsigned int size = match_size(match);
    if (size%2==0){
        correct_match = true;
        war_match snd = match;
        war_match fst = NULL;
        while (snd!=NULL){
            fst = snd;
            snd = snd->next;
            correct_match &= card_player(fst->card)==1 && card_player(snd->card)==2;
            snd = snd->next;
        }
    }
    return correct_match;
}

static unsigned int player_score(war_match match, unsigned int player) {
    unsigned int score = 0;
    if (is_match_correct(match)){
        unsigned int scorePlayerOne = 0;
        unsigned int scorePlayerTwo = 0;        
        war_match snd = match;
        war_match fst = match;
        while (snd!=NULL){
            fst = snd;
            snd = snd->next;
            if (card_wins(fst->card,snd->card)){
                scorePlayerOne += card_match_points(fst->card,snd->card);
            }
            else if (card_wins(snd->card,fst->card)){
                scorePlayerTwo += card_match_points(fst->card,snd->card);
            }                
            snd = snd->next;
        }
        if (player==1){
            score = scorePlayerOne;
        }    
        else if (player==2){
            score = scorePlayerTwo;
        }
    }
    return score;
}

unsigned int winner_total_points(war_match match) {
    unsigned int winnerPoints = 0;
    if (is_match_correct(match)){
        unsigned int scorePlayerOne = player_score(match,1);
        unsigned int scorePlayerTwo = player_score(match,2);
        if (scorePlayerOne > scorePlayerTwo){
            winnerPoints = scorePlayerOne;
        }
        else{
            winnerPoints = scorePlayerTwo;
        }
    }
    return winnerPoints;
}

card * match_to_array(war_match match) {
    card *array = NULL;
    if (match->card!=NULL){
        unsigned int size = match_size(match);
        array = calloc(size,sizeof(card));
        war_match curr = match;
        for (unsigned int i=0; i<size; ++i){
            array[i] = curr->card;
            curr = curr->next;
        }
    }
    return array;
}

void match_dump(war_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

war_match match_destroy(war_match match) {
  assert(match!=NULL);
  war_match curr = match;
  while (curr!=NULL){
    war_match killme = curr;
    curr = curr->next;
    killme->card = card_destroy(killme->card);
    free(killme);
  }
  match = NULL;
  return match;
}