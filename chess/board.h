#pragma once
#define COL 8
#define ROW 8

typedef struct Board{
    char board[ROW][COL];
} Board;

Board* init_board(Board* board);
void print_board(Board* board);

