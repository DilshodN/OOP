#pragma once

#include "board.h"
#include "queen.h"
#include "queue.h"

Queue* parse_data(const char* file_name, Board* board);
void delete_data(void* _queue);