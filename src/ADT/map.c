#include "map.h"
#include <string.h>
#include <stdlib.h>

static char *mapstrdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *dst = (char *)malloc(len);
    if (dst != NULL) {
        memcpy(dst, src, len);
    }
    return dst;
}

int hash(char* key, int capacity) {
    unsigned long hashVal = 5381;
    int c;

    while ((c = *key++)) {
        hashVal = ((hashVal << 5) + hashVal) + c;
    }

    return (int)(hashVal % capacity);
}

void CreateMap(Map *M){
    M->capacity = CACHE_MAX_AMOUNT;
    if (M->capacity > MAX_CAPACITY) M->capacity = MAX_CAPACITY;
    M->buffer = (Node**)calloc(MAX_CAPACITY, sizeof(Node*));
    M->size = 0;
    M->head = NULL;
    M->tail = NULL;
}

void DestroyMap(Map *M) {
    if (M == NULL) return;
    if (M->buffer != NULL) {
        for (int i = 0; i < MAX_CAPACITY; i++) {
            Node *cur = M->buffer[i];
            while (cur != NULL) {
                Node *next = cur->mapNext;
                free(cur->key);
                free(cur->value);
                free(cur);
                cur = next;
            }
        }
        free(M->buffer);
    }

    M->buffer = NULL;
    M->capacity = 0;
    M->size = 0;
    M->head = NULL;
    M->tail = NULL;
}

boolean isEmptyMap(Map *M){
    return M->size == 0;
}

void gotoRecentMap(Map *M, Node* n) {
    if(M->head == n) return;
    if(n->prev) {
        n->prev->next = n->next;
    }
    if(n->next) {
        n->next->prev = n->prev;
    }
    if(M->tail == n){
        M->tail = n->prev;
    }

    n->next = M->head;
    n->prev = NULL;

    if (M->head) {
        M->head->prev = n;
    }
    M->head = n;

    if (M->tail == NULL) {
        M->tail = n;
    }
}

void setMap(char* key, char* value, Map *M){
    int i = hash(key, M->capacity);
    Node* cur = M->buffer[i];

    while (cur != NULL) {
        if(strcmp(cur->key, key) == 0){
            free(cur->value);
            cur->value = mapstrdup(value);
            gotoRecentMap(M, cur);
            return;
        }
        cur = cur->mapNext;
    }

    if (M->size >= M->capacity && M->tail != NULL) {
        unsetMap(M->tail->key, M);
    }

    Node* setNode = (Node*)calloc(1,sizeof(Node));
    setNode->key = mapstrdup(key);
    setNode->value = mapstrdup(value);
    
    setNode->mapNext = M->buffer[i];
    M->buffer[i] = setNode;

    setNode->next = M->head;
    setNode->prev = NULL;
    if (M->head) {
        M->head->prev = setNode;
    }
    M->head = setNode;
    if (M->tail == NULL) {
        M->tail = setNode;
    }

    M->size++;
}

void unsetMap(char* key, Map *M){
    int i = hash(key, M->capacity);
    Node* cur = M->buffer[i];
    Node* prev = NULL;
    while (cur != NULL) {
        if(strcmp(cur->key, key) == 0){
            if(prev == NULL){
                M->buffer[i] = cur->mapNext;
            }
            else{
                prev->mapNext = cur->mapNext;
            }

            if(cur->prev){
                cur->prev->next = cur->next;
            }
            if(cur->next){
                cur->next->prev = cur->prev;
            }
            if(M->head == cur){
                M->head = cur->next;
            }
            if(M->tail == cur){
                M->tail = cur->prev;
            }
            
            free(cur->key);   
            free(cur->value); 
            free(cur);

            M->size--;
            return;
        }
        prev = cur;
        cur = cur->mapNext;
    }
}

char* getMap(char* key, Map *M){
    int i = hash(key, M->capacity);
    Node* cur = M->buffer[i];

    while (cur != NULL) {
        if(strcmp(cur->key, key) == 0){
                gotoRecentMap(M, cur);
                return cur->value;
            }
        cur = cur->mapNext;
    }
    return NULL;
}