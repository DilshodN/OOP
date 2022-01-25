#include "queue.h"

#include <stdlib.h>

struct Queue {
    void** data;

    size_t size;
    size_t count;
};

void* queue_init() {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue)
        return NULL;

    queue->data = NULL;
    queue->count = 0;
    queue->size = 0;
    return queue;
}

bool enqueue(void* _queue, dtype elem) {
    Queue* queue = _queue;
    if (!queue)
        return false;

    if (queue->count >= queue->size) {

        if (queue->size == 0)
            queue->size = 1;
        else
            queue->size *= 2;

        void** newData = realloc(queue->data, queue->size * sizeof(dtype));
        if (newData == NULL) {
            free(queue->data);
            return false;
        }
        queue->data = newData;
    }

    (queue->data)[queue->count++] = elem;
    return true;
}

size_t queue_count(void* _queue) {
    Queue* queue = _queue;
    if (!queue || !queue->data)
        return 0;
    return queue->count;
}

dtype queue_get(void* _queue, size_t index) {
    Queue* queue = _queue;
    if (!queue || !queue->data || index >= queue->count)
        return NULL;

    return queue->data[index];
}

void queue_destroy(void* _queue, void(*destroy)(void*)) {
    Queue* queue = _queue;
    if (!queue || !queue->data)
        return;

    for (size_t i = 0; i < queue->count; i++)
        destroy(queue->data[i]);
    free(queue->data);
    free(queue);
}