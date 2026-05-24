#include "set.h"

void CreateWeb(WebPages *W){
    W->NEff = 0;
}

void AddWeb(WebPages *W, int id, char* url, char* content){
    if (!isFullWeb(*W)) {
        if (isUniqueWeb(*W, url)) {
            W->buffer[W->NEff].id = id; 
            strcpy(W->buffer[W->NEff].web_url, url);
            strcpy(W->buffer[W->NEff].content, content);
            W->NEff++;
        }
    }
}

void RemoveWeb(WebPages *W, int id){
    int idx = -1;
    boolean found = false;

    for (int i = 0; i < W->NEff && !found; i++) {
        if (W->buffer[i].id == id) {
            idx = i;
            found = true;
        }
    }
    
    if (idx != -1) {
        for (int i = idx; i < W->NEff - 1; i++) {
            W->buffer[i] = W->buffer[i+1];
        }
        W->NEff--;
    }
}

boolean isUniqueWeb(WebPages W, char* url){
    for (int i = 0; i < W.NEff; i++)
    {
        if(strcmp(url, W.buffer[i].web_url) == 0){
            return false;
        }
    }
    return true;
}

boolean isEmptyWeb(WebPages W){
    return W.NEff == 0;
}

boolean isFullWeb(WebPages W){
    return W.NEff == 100;
}

char* FindURLbyID(WebPages *W, int id){
    for (int i = 0; i < W->NEff; i++)
    {
        if (W->buffer[i].id == id) {
            return W->buffer[i].web_url;
        }
    }
    return NULL;
}

char* getWeb(char* url, WebPages *W){
    for (int i = 0; i < W->NEff; i++)
    {
        if (strcmp(W->buffer[i].web_url, url) == 0) {
            return W->buffer[i].content;
        }
    }
    return NULL;
}
