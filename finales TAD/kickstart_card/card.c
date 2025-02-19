#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "card.h"

struct _s_card {
  unsigned int number;
  char suit;
  unsigned int player;
};

#define DIAMANTE  "DIAMANTE"
#define TREBOL    "TREBOL"
#define CORAZON   "CORAZON"
#define PICA      "PICA"

#define ROJO      "ROJO"
#define NEGRO     "NEGRO"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'd') {
        str = DIAMANTE;
    } else if (p=='t') {
        str = TREBOL;
    } else if (p=='c') {
        str = CORAZON;
    } else {
        str = PICA;
    }
    return str;
}

/* Representation invariant */

static bool valid_suit(char p) {
  return p=='d' || p=='t' || p=='c' || p=='p';
}

static bool valid_player(int p) {
  return p==1 || p==2;
}

static bool invrep(card c) {
    bool valid_card=false;
    valid_card = c!=NULL &&
                  1 <= c->number && c->number <= 13 &&
                  valid_suit(c->suit) &&
                  valid_player(c->player);
    return valid_card;
}

/* Public functions */

card card_new(unsigned int num, char suit, unsigned int player) {
  assert(1 <= num && num <= 13 && valid_suit(suit) && valid_player(player));
  struct _s_card *new_card = malloc(sizeof(struct _s_card));
  new_card->number = num;
  new_card->suit = suit;
  new_card->player = player;
  return new_card;
}

unsigned int card_player(card c) {
  return c->player;
}

unsigned int card_number(card c) {
  return c->number;
}

char card_color(card c) {
  char color = 'n';
  if (card_suit(c) == 'c' || card_suit(c) == 'd') {
    color = 'r';
  }
  return color;
}

char card_suit(card c) {
  return c->suit;
}

bool card_equal_color(card fst, card snd) {
  return card_color(fst)==card_color(snd);
}

unsigned int card_pair_points(card fst, card snd, unsigned int player) {
  unsigned int player_score = 0;
  if (player == 1){
    if (card_color(fst)==card_color(snd)){
      player_score = 1;
    }
  }
  else if (player == 2){
    if (fst->number==snd->number){
      player_score = 10;
    }
  }
  return player_score;
}

void card_dump(card c) {
  assert(invrep(c));
  printf("(%2d, %-7s, %2d)", c->number, suit_str(c->suit), c->player);
}

card card_destroy(card c) {
  assert(invrep(c));
  free(c);
  c = NULL;
  return c;
}
