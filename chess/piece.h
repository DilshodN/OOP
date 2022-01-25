#pragma once
#include "new.h"
#include "board.h"


struct Piece {
    const void *class;
    int x, y;
    Board* board;
};

extern const void* Piece;