#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"
#define MAX_CAPACITY 13

typedef struct Node{
    char* key;
    char* value;
    struct Node* mapNext;
    struct Node* prev; 
    struct Node* next;
} Node;

typedef struct {
    Node** buffer;
    int capacity;
    int size;

    Node* head; 
    Node* tail;
} Map;

void CreateMap(Map *M);

void DestroyMap(Map *M);

boolean isEmptyMap(Map *M);

void gotoRecentMap(Map *M, Node* n);

void setMap(char* key, char* value, Map *M);

void unsetMap(char* key, Map *M);

char* getMap(char* key, Map *M);


#endif