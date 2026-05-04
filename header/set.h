
#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <string.h>


#include "boolean.h"

typedef struct {
    int id;
    char* web_url[100];
    char* content[1000];
} Web;

typedef struct {
    Web buffer[100]; 
    int NEff;            
} WebPages;


void CreateWeb(WebPages *W);

void AddWeb(WebPages *W, int id, char* url, char* content);

void RemoveWeb(WebPages *W, int id);

boolean isUnique(WebPages W, char url);

boolean isEmpty(WebPages W);

boolean isFull(WebPages W);

int FindURLbyID(WebPages W, int id);

void PrintWeb(WebPages W);

#endif