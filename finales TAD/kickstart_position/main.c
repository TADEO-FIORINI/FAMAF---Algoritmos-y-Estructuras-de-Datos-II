#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"
int main()
{
   
    printf("Selecciona la dimension de la matriz: ");
    unsigned int dimension;
    scanf("%u",&dimension);
    struct _position *pos = position_initial(dimension);
    bool ready = false;
    while (!ready){
        printf("\nPosicion actual: (%u,%u)\n",position_row(pos),position_column(pos));
        printf("1) moverse a la derecha\n2) moverse a la izquierda\n3) moverse abajo\n4) moverse arriba\n0) quedarse en la posicion actual\n");
        unsigned int select;
        scanf("%u",&select);
        if (select==1){
            pos = position_right(pos);
        }
        else if (select==2){
            pos = position_left(pos);
        }
        else if (select==3){
            pos = position_down(pos);
        }
        else if (select==4){
            pos = position_up(pos);
        }
        else{
            ready = true;
        }
    }
    printf("\nEJEMPLO MATRIZ: \n");
    unsigned int **board = position_board(pos);
    for (unsigned int r = 0; r < dimension; ++r){
        for (unsigned int c = 0; c < dimension; ++c){
            printf(" %u", board[r][c]);
        }
        printf("\n");
    }
    printf("\nPara llegar a la posicion (%u,%u) nos movemos a partir de (0,0) como sigue: ",position_row(pos),position_column(pos));
    list_t list = list_empty();
    list = position_movements(pos);
    list_show(list);
    printf("\n\n");
    //destruir
    list = list_destroy(list);
    board = board_destroy(board,pos);
    pos = position_destroy(pos);
    return 0;
}