#include <stdlib.h>

#include "search.h"
#include "set.h"

void makeLowerCase(char* s, char* sL, int len){
    for (int i = 0; i < len; i++) 
    {
        if(s[i] >= 'A' && s[i] <= 'Z'){
            sL[i] = s[i] + 32;
        } 
        else{
            sL[i] = s[i];
        }
    }
    sL[len] = '\0'; 
}

void badChar(char* s, int len, int bc[]){
    for (int i = 0; i < 256; i++) bc[i] = -1;
    
    for (int i = 0; i < len; i++)
    {
        int j = (int) s[i];
        bc[j] = i;
    }
}

void goodSuffix(char* s, int len, int shift[], int b[]){
    for (int i = 0; i <= len; i++)
    {
        shift[i] = 1;
        b[i] = -1;
    }

    for (int i = 1; i < len; i++)
    {
        char* suffix = &s[len - i];
        for (int j = 0; j < len - i; j++)
        {
            int match = 1;
            for (int k = 0; k < i && match; k++)
            {
                if(suffix[k] != s[j + k]){
                    match = 0;
                }
            }
            if(match){
                b[i] = j;
                shift[i] = len - j - i;
                if (shift[i] < 1) shift[i] = 1;  
            }
        }
    }
    shift[0] = 1;
}

void boyerMoore(char* s, WebPages W){
    int m = strlen(s);

    char lowerS[m + 1];
    makeLowerCase(s, lowerS, m);

    int bc[256];
    int shift[m + 1];
    int border[m + 1];

    badChar(lowerS, m, bc);
    goodSuffix(lowerS, m, shift, border);

    int count = 0;

    for (int idx = 0; idx < W.NEff; idx++)
    {
        char* contentext[2] ={W.buffer[idx].web_url, W.buffer[idx].content};
        boolean found = false;

        for (int t = 0; t < 2 && !found; t++) 
        {
            char* text = contentext[t];
            int n = strlen(text);
            
            char lowerT[1000000];
            makeLowerCase(text, lowerT, n);

            int i = m - 1;

            while(i < n && !found){
                int j = m - 1;
                int mismatch = 0;
                
                while(j >= 0 && !mismatch){
                    int pos = i - (m - 1 - j);
                    if(lowerS[j] != lowerT[pos]){
                        mismatch = 1;
                    } 
                    else{
                        j--;
                    }
                }

                if(j < 0){
                    printf("[%d] %s\n", idx+1, contentext[0]);
                    found = true;
                    count++;
                } 
                else{
                    int pos = i - (m - 1 - j);
                    int bcS = j - bc[(int)lowerT[pos]];
                    if(bcS < 1) bcS = 1;
                    int gsS = shift[j + 1];

                    if(bcS > gsS){
                        i += bcS;
                    }
                    else{
                        i += gsS;
                    }
                }
            }
        }
    }
    if(!count) printf("-\n");
}