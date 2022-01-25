#ifndef _queue_h
#define _queue_h

#include <stdbool.h>
#include <stddef.h>

typedef struct Queue Queue;
typedef void* dtype;

void* queue_init();
bool enqueue(void* _queue, dtype elem);
size_t queue_count(void* _queue);
dtype queue_get(void* _queue, size_t index);
void queue_destroy(void* _queue, void(*destroy)(void*));

#endif