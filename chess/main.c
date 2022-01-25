#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "board.h"
#include "queue.h"
#include "new.h"
#include "piece.h"


int main(int argc, char* argv[]) {
    const char* file_name = NULL;
    if (argc > 1)
        file_name = argv[1];
    if (file_name == NULL) {
        printf("no input file\n");
        return -1;
    }
    Board board;
    init_board(&board);
    void* figures = parse_data(file_name, &board);
    if (figures == NULL) {
        printf("no figures\n");
        return -1;
    }
    print_board(&board);
    for (size_t i = 0; i < queue_count(figures); ++i)
        check_attack(queue_get(figures, i));

    queue_destroy(figures, delete);
    return 0;
}