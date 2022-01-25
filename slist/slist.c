#include "slist.h"
#include <stdio.h>
#include <mm_malloc.h>
#include <memory.h>
#define STOP (size_t)NULL

typedef struct Node{
    void* value;
    struct Node* next;
} Node;

typedef struct Llist{
    Node* head;
    size_t lenght;
    size_t  itemSize;
} LinkList;


void* slist_create(size_t itemSize){
    if(itemSize == 0)
        return NULL;
    LinkList* llist = (LinkList*)malloc(sizeof(LinkList));
    if(llist == NULL)
        return NULL;
    llist->head = NULL;
    llist->lenght = 0;
    llist->itemSize = itemSize;
    return llist;
}

void slist_destroy(void* slist, void(*destroy)( void * )){
    if(slist != NULL)
        slist_clear(slist, destroy);
    free(slist);
}

void* slist_init(void * slist, size_t itemSize, void(*destroy)(void*)){
    if(itemSize == 0)
        return NULL;
    if(slist != NULL){
        slist_clear(slist, destroy);
        ((LinkList*)slist)->itemSize = itemSize;
        return slist;
    }
    return slist;
}

void slist_clear(void * slist, void(*destroy)( void * )){
    if(slist != NULL)
        while (((LinkList*)slist)->lenght > 0)
            slist_remove(slist, destroy);
}


size_t slist_count(const void * slist){
    if(slist == NULL)
        return INVALID;
    const LinkList* llist = slist;
    return llist->lenght;
}

void* slist_item(void * slist, size_t i){
    if(slist == NULL)
        return NULL;
    LinkList* llist = slist;
    if(i >= llist->lenght)
        return NULL;
    if(llist->head != NULL) {
        Node* tmp = llist->head;
        while (i--) {
            tmp = tmp->next;
        }
        return tmp->value;
    }
    else
        return NULL;
}

static void* slist_node(void * slist, size_t i){
    if(slist == NULL)
        return NULL;
    LinkList* llist = slist;
    if(i >= llist->lenght)
        return NULL;
    if(llist->head != NULL) {
        Node* tmp = llist->head;
        while (i--) {
            tmp = tmp->next;
        }
        return tmp;
    }
    return NULL;
}

static Node* create_node(LinkList* slist) {
    if (slist == NULL) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL){
        return NULL;
    }
    node->value = malloc(slist->itemSize);
    if (node->value == NULL){
        free(node);
        return NULL;
    }
    memset(node->value, 0, slist->itemSize);
    node->next = NULL;
    return node;
}

void* slist_prepend(void * slist) {
    if (slist == NULL)
        return NULL;

    LinkList* llist = slist;
    if(llist->head == NULL){
        llist->head = create_node(llist);
        llist->lenght ++;
        return llist->head->value;
    }
    else{
        Node *newNode = create_node(llist);
        newNode->next = llist->head;
        llist->head = newNode;
        llist->lenght ++;
        return newNode->value;
    }

}


void slist_remove(void * slist, void(*destroy)( void * )){
    if(slist != NULL) {
        Node* tmp = ((LinkList*)slist)->head;
        if(tmp != NULL) {
            if(tmp->value != NULL){
                if(destroy != NULL)
                    destroy(tmp->value);
                free(tmp->value);
            }
            ((LinkList*)slist)->head = tmp->next;
            ((LinkList*)slist)->lenght --;
        }
        free(tmp);
    }
}

size_t slist_first(const void * slist){
    LinkList* self = (LinkList*)slist;
    if (self == NULL) return STOP;
    return (size_t)self->head;
}


static Node* find_prev(LinkList* list, Node* node) {
    if (list->head == NULL || list->head == node)
        return NULL;
    for (Node *prev = list->head; prev->next != NULL; prev = prev->next) {
        if (prev->next == node)
            return prev;
    }
    return NULL;
}


size_t slist_next(const void * slist, size_t item_id){
    LinkList* self = (LinkList*)slist;
    if (self == NULL) return STOP;
    if (item_id == STOP) return STOP;
    Node* node = (void*)item_id;
    return (size_t)node->next;
}


size_t slist_stop(const void * slist){
    slist;
    return STOP;
}

void* slist_current(const void * slist, size_t item_id){
    if(slist == NULL || item_id == STOP){
        return NULL;
    }
    return ((Node*)item_id)->value;
}

void* slist_insert(void * slist, size_t item_id) {
    if (slist == NULL)
        return NULL;
    LinkList *llist = slist;

    if (llist->head == NULL && item_id == STOP) {
        slist_prepend(slist);
        return ((Node*)slist_first(slist))->value;
    }

    if (llist->head != NULL && item_id != STOP){
        Node *node = (Node*)item_id;
        Node* newNode = create_node(llist);
        if(node->next == NULL){
            node->next = newNode;
            llist->lenght ++;
            return newNode->value;
        }
        if(node->next != NULL){
            newNode->next = node->next;
            node->next = newNode;
            llist->lenght ++;
            return newNode->value;
        }


    }
    return NULL;
}

void slist_erase(void * slist, size_t item_id, void(*destroy)( void * )) {
    if (slist != NULL) {
        LinkList *llist = slist;
        if (llist->head != NULL) {
            if (item_id != STOP) {
                Node *node = (Node*)item_id;
                if (node == llist->head) {
                    slist_remove(slist, destroy);
                    return;
                }
                Node* prev_node = find_prev(llist, node);
                prev_node->next = node->next;
                if(destroy != NULL)
                    destroy(node->value);
                free(node->value);
                free(node);
                llist->lenght --;

            }
        }
    }
}