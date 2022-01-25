#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "run.h"
#include "board.h"
#include "new.h"

#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"

#include "queue.h"

#define BUFF_SIZE 256
#define KING "king"
#define QUEEN "queen"
#define ROOK "rook"
#define BISHOP "bishop"
#define KNIGHT "knight"


static void* parse(const char* str, Board* board){
    if(!str) return NULL;

    char objName[BUFF_SIZE];
    int x, y;
    int num = sscanf(str, "%s %d %d", objName, &x, &y);

    objName[BUFF_SIZE - 1] = '\0';

    if(num == -1) return NULL;
    else if(!strcmp(objName, KING))   return new(King, x, y, board);
    else if(!strcmp(objName, QUEEN))  return new(Queen, x, y, board);
    else if(!strcmp(objName, ROOK))   return new(Rook, x, y, board);
    else if(!strcmp(objName, BISHOP)) return new(Bishop, x, y, board);
    else if(!strcmp(objName, KNIGHT)) return new(Knight, x, y, board);
    else {
        printf("Incorrect param count in str: %s\n", str);
        return NULL;
    }
}

Queue* parse_data(const char* file_name, Board* board){
    FILE* F = fopen(file_name, "r");
    if(F == NULL){
        printf("Can't open!");
        return NULL;
    }

    void* queue = queue_init();
    char str[BUFF_SIZE];
    while(fgets(str, BUFF_SIZE, F)){
        void* piece = parse(str, board);
        if(!piece)
            continue;
        if(!enqueue(queue, piece))
            break;
    }
    fclose(F);
    return queue;
}

void delete_data(void* _queue) {
    Queue* queue = _queue;
    if (!queue)
        return;

    queue_destroy(queue, delete);
}