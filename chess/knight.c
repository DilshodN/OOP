#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "knight.h"
#include "new.h"

static void* knight_ctor(void* _self, va_list* app){
    struct Knight* self = NULL;

    if (_self) {
        // вызов конструктора базового класса
        self = ((const struct Class*)Piece)->ctor(_self, app);

        if(!((self->_piece.x > 7 || self->_piece.y > 7) || (self->_piece.x < 0 ||self->_piece.y < 0)))
            self->_piece.board->board[self->_piece.x][self->_piece.y] = 'N';
    }
    return self;
}

static void check_knight(const void* self) {
    const struct Piece* _piece = self;

    int x = _piece->x;
    int y = _piece->y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (_piece->board->board[i][j] == '_' || (i == x && j == y))
                continue;
            char piece = _piece->board->board[i][j];
            int deltaX = abs(x - i);
            int deltaY = abs(y - j);
            if ((deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2))
                printf("N at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
        }
    }
}


static const struct Class _Knight = {sizeof(struct Piece), knight_ctor, NULL, check_knight};
const void* Knight = &_Knight;