#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    card_t card;
    player_t player;
    struct s_ugame *next;
};

unogame_t
uno_newgame(card_t card) {
    unogame_t uno = malloc(sizeof(struct s_ugame));
    uno->card = card;
    uno->next = NULL;
    uno->player = NO_PLAYER;
    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    unogame_t new_game = uno_newgame(c);
    new_game->player = uno_nextplayer(uno); 
    new_game->next = uno;
    uno = new_game;
    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    unsigned int size = 0;
    unogame_t curr = uno;
    while (curr!=NULL){
        size++;
        curr = curr->next;
    }
    return size;
}

bool
uno_validpile(unogame_t uno) {
    bool valid_pile = true;
    unogame_t curr = uno;
    unogame_t prev = NULL; 
    while (curr!=NULL && curr->next!=NULL){
        prev = curr;
        curr = curr->next;
        valid_pile &= card_compatible(prev->card,curr->card); 
    }
    valid_pile &= card_get_type(curr->card)!=change_color;
    return valid_pile;
}

color_t
uno_currentcolor(unogame_t uno) {
    return card_get_color(uno->card);
}

player_t
uno_nextplayer(unogame_t uno) {
    player_t next_player;
    type_t type = card_get_type(uno->card);
    
    if (type==normal || type==change_color){
        next_player = (uno->player + 1) % NUM_PLAYERS;
    }
    else if (type == skip){
        next_player = (uno->player + 2) % NUM_PLAYERS;
    }
    /*
    if (type==normal || type==change_color){
        if (uno->player==NO_PLAYER || uno->player==NUM_PLAYERS-1){
            next_player = 0;
        }
        else if (NO_PLAYER<uno->player && uno->player<NUM_PLAYERS-1){
            next_player = uno->player + 1;
        }
    }
    else if (type==skip){
        if (uno->player==NUM_PLAYERS-2){
            next_player = 0;
        }
        else if (uno->player==NO_PLAYER || uno->player==NUM_PLAYERS-1){
            next_player = 1;
        }
        else if (NO_PLAYER<uno->player && uno->player<NUM_PLAYERS-2){
            next_player = uno->player + 2;
        }
    }
    */
    return next_player;
}


card_t *
uno_pile_to_array(unogame_t uno) {
    card_t *array = NULL;
    unsigned int size = uno_count(uno);
    if (size!=0){
        array = calloc(size,sizeof(card_t));
        unogame_t current = uno;
        for (unsigned int i=1; i<=size; ++i){
            array[size-i] = current->card;
            current = current->next;
        }
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    struct s_ugame *current = uno;
    while (current!=NULL){
        struct s_ugame *killme = current;
        current = current->next;
        killme->card = card_destroy(killme->card);
        free(killme);

    }
    uno = NULL;
    return uno;
}


