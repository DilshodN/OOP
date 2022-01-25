#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "bishop.h"
#include "new.h"
#include "diag_horiz.h"

static void* bishop_ctor(void* _self, va_list* app){
    struct Bishop* self = NULL;

    if (_self) {
        // вызов конструктора базового класса
        self = ((const struct Class*)Piece)->ctor(_self, app);

        if(!((self->_piece.x > 7 || self->_piece.y > 7) || (self->_piece.x < 0 ||self->_piece.y < 0)))
            self->_piece.board->board[self->_piece.x][self->_piece.y] = 'B';
    }
    return self;
}


static void check_bishop(const void* self){
    const struct Piece* _piece = self;
    int x = _piece->x;
    int y = _piece->y;

    int c1 = x - y;
    int c2 = x + y;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (_piece->board->board[i][j] == '_' || (i == x && j == y))
                continue;

            char piece = _piece->board->board[i][j];
            if((i - j == c1) || (i + j) == c2){
                if((i - j) == c1) {
                    int min_x = i < x ? i : x;
                    int min_y = j < y ? j : y;
                    int max_x = i > x ? i : x;
                    int max_y = j > y ? j : y;
                    if(nobody_in_diag1(min_x + 1, min_y + 1, max_x - 1, max_y - 1, _piece->board))
                        printf("B at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
                }
                if((i + j) == c2){
                    int min_x = i < x ? i : x;
                    int min_y = j < y ? j : y;
                    int max_x = i > x ? i : x;
                    int max_y = j > y ? j : y;
                    if(nobody_in_diag2(min_x + 1, max_y - 1, max_x - 1, min_y + 1, _piece->board))
                        printf("B at (%d, %d) beats %c at (%d, %d) \n", x, y, piece, i, j);
                }
            }

        }
    }
}

static const struct Class _Bishop = {sizeof(struct Piece), bishop_ctor, NULL, check_bishop};
const void* Bishop = &_Bishop;