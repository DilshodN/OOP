#pragma once

#include "board.h"

int nobody_in_horiz(int line, int y1, int y2, Board* board);
int nobody_in_vert(int row, int x1, int x2, Board* board);
int nobody_in_diag1(int x1, int y1, int x2, int y2, Board* board);
int nobody_in_diag2(int x1, int y1, int x2, int y2, Board* board);