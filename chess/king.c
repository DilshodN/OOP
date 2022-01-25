#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

#include "king.h"
#include "new.h"

static void* king_ctor(void* _self, va_list* app){
    struct King* self = NULL;

    if (_self) {
        // вызов конструктора базового класса
        self = ((const struct Class*)Piece)->ctor(_self, app);

        if(!((self->_piece.x > 7 || self->_piece.y > 7) || (self->_piece.x < 0 ||self->_piece.y < 0)))
            self->_piece.board->board[self->_piece.x][self->_piece.y] = 'K';
    }
    return self;
}

static void check_king(const void* self) {
    const struct Piece* _piece = self;

    int x = _piece->x;
    int y = _piece->y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (_piece->board->board[i][j] == '_' || (i == x && j == y))
                continue;
            char piece = _piece->board->board[i][j];
            if (abs(x - i) <= 1 && abs(y - j) <= 1)
                printf("K at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
        }
    }
}

const struct Class _King = {sizeof(struct Piece), king_ctor, NULL, check_king};
const void* King = &_King;