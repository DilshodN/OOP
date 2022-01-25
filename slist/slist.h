#include <stddef.h>  // size_t

static const size_t INVALID = ~((size_t)0);

void* slist_create(size_t itemSize);
void slist_destroy(void * slist, void(*destroy)( void * ));

void* slist_init(void * slist, size_t itemSize, void(*destroy)(void*));
void slist_clear(void * slist, void(*destroy)( void * ));

size_t slist_count(const void * slist);
void* slist_item(void * slist, size_t i);
void* slist_prepend(void * slist);
void slist_remove(void * slist, void(*destroy)( void * ));

size_t slist_first(const void * slist);
size_t slist_next(const void * slist, size_t item_id);
size_t slist_stop(const void * slist);
void* slist_current(const void * slist, size_t item_id);
void* slist_insert(void * slist, size_t item_id);
void slist_erase(void * slist, size_t item_id, void(*destroy)( void * ));