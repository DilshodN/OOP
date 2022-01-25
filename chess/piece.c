#include <stdarg.h>
#include "piece.h"

static void* Piece_ctor(void* _self, va_list* app)
{
    struct Piece* self = NULL;
    if (_self)
    {
        self = (struct Piece*)_self;
        self->x = va_arg(*app, int);
        self->y = va_arg(*app, int);
        self->board = va_arg(*app, Board*);
    }
    return self;
}

static const struct Class _Piece = {
        sizeof(struct Piece),
        Piece_ctor,
        NULL,
        NULL // не имеет реализации функции check_attack
};
// end of file piece.c


const void* Piece = &_Piece;


