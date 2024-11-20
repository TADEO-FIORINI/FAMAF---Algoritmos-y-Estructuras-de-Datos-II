#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    bool valid_color = c->color==blue || c->color==red || c->color==yellow || c->color==green; 
    bool valid_num = c->num==0 || c->num==1 || c->num==2 || c->num==3 || c->num==4 || c->num==5
        || c->num==6 || c->num==7 || c->num==8 || c->num==9;
    bool valid_type = c->type==normal || c->type==change_color || c->type==skip;
    bool valid=false;
    valid = c!=NULL && valid_color && valid_num && valid_type;
    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    card_t card=NULL;
    card = malloc(sizeof(struct s_card));
    card->num = num;
    card->color = color;
    card->type = s;
    assert(invrep(card));
    return card;
}


type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    return c1->color==c2->color;
}


bool
card_samenum(card_t c1, card_t c2) {
    return c1->num==c2->num;
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));
    if (new_card->type==change_color){
        compatible = true;
    }
    else if (pile_card->type==skip){
        bool twese_skip = new_card->type==skip && pile_card->type==skip; 
        compatible = card_samecolor(new_card,pile_card) || twese_skip;
    }
    else if (pile_card->type==change_color){
        compatible = card_samecolor(new_card,pile_card);
    }
    else {
        compatible = card_samecolor(new_card,pile_card) || card_samenum(new_card,pile_card);      
    }
    return compatible;
}

card_t
card_destroy(card_t card) {
    assert(invrep(card));
    free(card);
    card = NULL;
    return card;
}


