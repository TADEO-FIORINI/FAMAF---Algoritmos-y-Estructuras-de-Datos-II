#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
    struct _position *pos = malloc(sizeof(struct _position));
    pos->row = 0;
    pos->column = 0;
    pos->dimension = dimension;
    return pos;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
    assert(row<dimension && column<dimension);
    position_t pos = position_initial(dimension);
    pos->row = row;
    pos->column = column;
    return pos;
}

position_t position_left(position_t pos)
{
    if (pos->column > 0){
        pos->column--;
    }
    else if (pos->column==0){
        pos->column = pos->dimension-1;
    }
    return pos;
}

position_t position_right(position_t pos)
{
    if (pos->column < pos->dimension-1){
        pos->column++;
    }
    else if (pos->column==pos->dimension-1){
        pos->column = 0;
    }
    return pos;
}

position_t position_down(position_t pos)
{
    if (pos->row < pos->dimension-1){
        pos->row++;
    }
    else if (pos->row==pos->dimension-1){
        pos->row = 0;
    }
    return pos;
}

position_t position_up(position_t pos)
{
    if (pos->row > 0){
        pos->row--;
    }
    else if (pos->row==0){
        pos->row = pos->dimension-1;
    }
    return pos;
}

unsigned int position_row(position_t pos)
{
    return pos->row;
}

unsigned int position_column(position_t pos)
{
    return pos->column;
}

unsigned int **position_board(position_t pos)
{
    unsigned int **board = NULL;
    board = calloc(pos->dimension,sizeof(unsigned int*));
    for (unsigned int row = 0; row < pos->dimension; ++row){
        board[row] = calloc(pos->dimension, sizeof(unsigned int));
    }
    board[pos->row][pos->column] = 1;
    return board;
}

unsigned int **board_destroy(unsigned int **board,position_t pos){
    for (unsigned int row = 0; row < pos->dimension; ++row){
        free(board[row]);
    }
    free(board);
    board = NULL;
    return board;
}

list_t position_movements(position_t pos)
{
    list_t list = list_empty();
    for (unsigned int column = 0; column < pos->column; ++column){
        list = list_append(list,RIGHT);
    }
    for (unsigned int row = 0; row < pos->row; ++row){
        list = list_append(list,DOWN);
    }
    return list;
}

position_t position_destroy(position_t pos)
{
    if (pos!=NULL){
        free(pos);
        pos = NULL;
    }
    return pos;
}