#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "rook.h"
#include "new.h"
#include "diag_horiz.h"

static void* rook_ctor(void* _self, va_list* app){
    struct Rook* self = NULL;

    if (_self) {
        // вызов конструктора базового класса
        self = ((const struct Class*)Piece)->ctor(_self, app);

        if(!((self->_piece.x > 7 || self->_piece.y > 7) || (self->_piece.x < 0 ||self->_piece.y < 0)))
        self->_piece.board->board[self->_piece.x][self->_piece.y] = 'R';
    }
    return self;
}


static void check_rook(const void* self) {
    const struct Piece* _piece = self;

    int x = _piece->x;
    int y = _piece->y;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (_piece->board->board[i][j] == '_' || (i == x && j == y))
                continue;

            char piece = _piece->board->board[i][j];
            if(i == x || j == y){
                if(x == i) {
                    int min_y = j < y ? j : y;
                    int max_y = j > y ? j : y;
                    if(nobody_in_horiz(x, min_y + 1, max_y - 1, _piece->board))
                        printf("R at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
                }
                if(j == y){
                    int min_x = i < x ? i : x;
                    int max_x = i > x ? i : x;
                    if(nobody_in_vert(y, min_x + 1, max_x - 1, _piece->board))
                        printf("R at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
                }
            }
        }
    }
}


static const struct Class _Rook = {sizeof(struct Piece), rook_ctor, NULL, check_rook};
const void* Rook = &_Rook;