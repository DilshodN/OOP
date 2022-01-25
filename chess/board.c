#include "board.h"
#include <stdio.h>

Board* init_board(Board* board){
    for(int i = 0; i < ROW; i ++)
        for(int j = 0; j < COL; j ++)
            board->board[i][j] = '_';
    return board;
}

void print_board(Board* board){
    for(int i = 0; i < ROW; i ++){
        for(int j = 0; j < COL; j ++) {
            printf("%c ", board->board[i][j]);
        }
        printf("\n");
    }
}