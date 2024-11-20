#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match {
    card card;
    struct _s_match *next;
};

cf_match match_new(void)
{
    struct _s_match *new_match = malloc(sizeof(struct _s_match));
    new_match->card = NULL;
    new_match->next = NULL;
    return new_match;
}

cf_match match_add(cf_match match, card c)
{
    if (match->card==NULL && match->next==NULL){
      match->card = c;
    }
    else if (match->card!=NULL){
      struct _s_match *new_match = match_new();
      new_match->card = c;
      new_match->next = NULL;
      struct _s_match *current = match;
      while (current->next!=NULL){
        current = current->next;
      }
      current->next = new_match;
    }
    return match;
}

unsigned int match_size(cf_match match)
{
    unsigned int size = 0;
    struct _s_match *current = match;
    while (current!=NULL){
        current = current->next;
        size++;
    }
    return size;
}

bool check_correct_players(card fst,card snd){
    return card_player(fst)==1 && card_player(snd)==2;
}

bool check_correct_colors(card fst,card snd,char color_fst,char color_snd){
    return card_color(fst)==color_fst && card_color(snd)==color_snd;
}

bool is_match_correct(cf_match match)
{
    //la cantidad de cartas es par, tiradas por el jugador 1 y el jugador 2 intercaladamente 
    //y las cartas que tira cada jugador son del mismo color
    bool correct = false;
    unsigned int size = match_size(match);
    if (size%2==0){
        correct = true;
        char colorPlayerOne = card_color(match->card);
        char colorPlayerTwo = card_color(match->next->card);
        struct _s_match *curr = match;
        struct _s_match *prev = NULL;
        while (curr!=NULL){
            prev = curr;
            curr = curr->next;
            correct &= check_correct_players(prev->card,curr->card) 
            && check_correct_colors(prev->card,curr->card,colorPlayerOne,colorPlayerTwo);
            curr = curr->next;
        }
    }
    return correct;
}

struct flushControl
{
    bool isFlushControl;
    bool upwardsFlushControl;
};

struct flushControl controlFlush(card fst,card snd,int points){
    //funcion auxiliar para actualizar los valores de isFlush y upwardsFlush al recorrer el maso para contar los puntos
    struct flushControl control;
    bool isFlush;
    bool upwardsFlush;
    if (points==-3){ 
        // se rompe la escalera
        isFlush = false;
    } 
    else if (points==5){
        isFlush = true; // se comienza o continua una escalera
        if (card_number(snd)==card_number(fst)+1){
            // el sentido es creciente
            upwardsFlush = true;
        }
        else if (card_number(snd)==card_number(fst)-1){
            // el sentido es decreciente
            upwardsFlush = false;
        }
        // para los puntos 0 y 7 los valores booleanos permanecen iguales
    }
    control.isFlushControl = isFlush;
    control.upwardsFlushControl = upwardsFlush;
    return control;
}

static int player_score(cf_match match, unsigned int player)
{
    bool isFlush = false;
    bool upwardsFlush = false;
    int score = 0;
    int playerOneScore = 0;
    int playerTwoScore = 0;
    if (is_match_correct(match)){
        struct flushControl control;
        struct _s_match *curr = match->next;
        struct _s_match *prev = match;
        //el jugador 2 siempre suma una vez mas que el jugador uno
        while (curr->next!=NULL){
            int playerTwoPoints = card_drop_points(prev->card,curr->card,isFlush,upwardsFlush);
            playerTwoScore += playerTwoPoints;
            control = controlFlush(prev->card,curr->card,playerTwoPoints);
            isFlush = control.isFlushControl;
            upwardsFlush = control.upwardsFlushControl;
            prev = curr;
            curr = curr->next;
            int playerOnePoints = card_drop_points(prev->card,curr->card,isFlush,upwardsFlush);
            playerOneScore += playerOnePoints;
            control = controlFlush(prev->card,curr->card,playerOnePoints);
            isFlush = control.isFlushControl;
            upwardsFlush = control.upwardsFlushControl;
            prev = curr;
            curr = curr->next;
        }
        playerTwoScore += card_drop_points(prev->card,curr->card,isFlush,upwardsFlush);
        if (player==1){
            score = playerOneScore;
        }
        else if (player==2){
            score = playerTwoScore;
        }
    }
    return score;
}
unsigned int match_winner(cf_match match)
{
    unsigned int winner = 0;
    int playerOneScore = player_score(match,1);
    int playerTwoScore = player_score(match,2);
    if (!is_match_correct(match)){
        winner = -1;
    }
    else if (playerOneScore<playerTwoScore){
        winner = 2;
    }
    else if (playerOneScore>playerTwoScore){
        winner = 1;
    }
    return winner;
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{
    unsigned int size = match_size(match);
    card *array = calloc(size,sizeof(card));
    struct _s_match *curr = match;
    for (unsigned int i=0; i<size; ++i){
        array[i] = curr->card;
        curr = curr->next;
    }
    return array;
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    struct _s_match *curr = match;
    while (curr!=NULL){
        struct _s_match *killme = curr;
        curr = curr->next;
        killme->card = card_destroy(killme->card);
        free(killme);
        killme = NULL;
    }
    match = NULL;
    return match;
}
