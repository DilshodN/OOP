#include "diag_horiz.h"


int nobody_in_horiz(int line, int y1, int y2, Board* board){
    for(; y1 < y2; y1 ++)
        if(board->board[line][y1] != '_')
            return 0;
    return 1;
}

int nobody_in_vert(int row, int x1, int x2, Board* board){
    for(; x1 < x2; x1 ++)
        if(board->board[x1][row] != '_')
            return 0;
    return 1;
}

int nobody_in_diag1(int x1, int y1, int x2, int y2, Board* board){
    for(int i = x1, j = y1; i <= x2; i ++, j++)
        if(board->board[i][j] != '_')
            return 0;
    return 1;
}

int nobody_in_diag2(int x1, int y1, int x2, int y2, Board* board){
    for(int i = x1, j = y1; i <= x2; i ++, j --)
        if(board->board[i][j] != '_')
            return 0;
    return 1;
}