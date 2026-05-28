
#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <string.h>

#include "boolean.h"
#include "config.h"

typedef struct {
    int id;
    char web_url[100];
    char content[10000];
} Web;

typedef struct {
    Web buffer[MAX_WEB_PAGES]; 
    int NEff;            
} WebPages;


void CreateWeb(WebPages *W);

void AddWeb(WebPages *W, int id, char* url, char* content);

void RemoveWeb(WebPages *W, int id);

boolean isUniqueWeb(WebPages W, char* url);

boolean isEmptyWeb(WebPages W);

boolean isFullWeb(WebPages W);

char* FindURLbyID(WebPages *W, int id);

char* getWeb(char* url, WebPages *W);


#endif