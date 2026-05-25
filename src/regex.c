#include "regex.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

boolean isNameValid(char* name){
    int len = strlen(name);

    if(len < 1 || len > 63) return false;

    if(name[0] == '-') return false;
    if(name[len - 1] == '-') return false;
    
    for(int i = 0; i < len; i++){
        if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9') || (name[i] == '-'))){
            return false;
        }
    }

    return true;
}

boolean isDomainValid(char* dom){
    int len = strlen(dom);

    if(len < 2) return false;
    for(int i = 0; i < len; i++){
        if(!((dom[i] >= 'A' && dom[i] <= 'Z') || (dom[i] >= 'a' && dom[i] <= 'z'))){
            return false;
        }
    }
    return true;
}

boolean isWebsiteValid(char* s){
    int len = strlen(s); 
    int iDot = -1;
    boolean found = false;
    for(int i = 0; i < len && !found; i++){
        if(s[i] == '.'){
            iDot = i;
            found = true;
        }
    }
    if(iDot > 0){
        char name[64]; 
        char dom[64];
        if (iDot > 63) return false;

        strncpy(name, s, iDot);
        name[iDot] = '\0';

        if (len-iDot-1 < 2) return false;
        strncpy(dom, s + iDot + 1, len-iDot-1);
        dom[len-iDot-1] = '\0';

        if(isNameValid(name) && isDomainValid(dom)) return true;
    }

    return false;
}