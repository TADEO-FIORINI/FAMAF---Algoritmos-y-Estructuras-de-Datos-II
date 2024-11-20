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
  card new_card = malloc(sizeof(card));
  new_card->number = num;
  new_card->player = player;
  new_card->suit = suit;
  return new_card;
}

unsigned int card_player(card c) {
  return c->player;
}

unsigned int card_number(card c) {
  return c->number;
}

char card_suit(card c) {
  return c->suit;
}

bool card_wins(card fst, card snd) {
  return fst->number > snd->number;
}

unsigned int card_match_points(card fst, card snd) {
  unsigned int points = 0;
  if (card_wins(fst,snd)){
    points = card_number(snd);
  }
  else if (card_wins(snd,fst)){
    points = card_number(fst);
  }
  return points;
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