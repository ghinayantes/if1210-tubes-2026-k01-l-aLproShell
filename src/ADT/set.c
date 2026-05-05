#include "../../header/set.h"

void CreateWeb(WebPages *W){
    W->NEff = 0;
}

void AddWeb(WebPages *W, int id, char* url, char* content){
    if (!isFull(*W)) {
        if (isUnique(*W, url)) {
            W->buffer[W->NEff].id = id; 
            strcpy(W->buffer[W->NEff].web_url, url);
            strcpy(W->buffer[W->NEff].content, content);
            W->NEff++;
        }
    }
}

void RemoveWeb(WebPages *W, int id){
    int idx = -1;

    for (int i = 0; i < W->NEff; i++) {
        if (W->buffer[i].id == id) {
            idx = i;
            break;
        }
    }
    
    if (idx != -1) {
        for (int i = idx; i < W->NEff - 1; i++) {
            W->buffer[i] = W->buffer[i+1];
        }
        W->NEff--;
    }
}

boolean isUnique(WebPages W, char* url){
    for (int i = 0; i < W.NEff; i++)
    {
        if(strcmp(url, W.buffer[i].web_url) == 0){
            return false;
        }
    }
    return true;
}

boolean isEmpty(WebPages W){
    return W.NEff == 0;
}

boolean isFull(WebPages W){
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

void PrintWeb(WebPages W);