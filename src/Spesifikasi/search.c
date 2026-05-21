#include "search.h"
#include "set.h"

void badChar(char* s, int len, int bc[]){
    for (int i = 0; i < 256; i++)
    {
        bc[i] = -1;
    }
    
    for (int i = 0; i < len; i++)
    {
        int j = (int) s[i];
        bc[j] = i;
    }
}

void goodSuffix(char* s, int len, int shift[], int b[]) {
    for (int i = 0; i <= len; i++) {
        shift[i] = 1;
        b[i] = -1;
    }

    for (int i = 1; i < len; i++) {
        char* suffix = &s[len - i];
        for (int j = 0; j < len - i; j++) {
            int match = 1;
            for (int k = 0; k < i; k++) {
                if (suffix[k] != s[j + k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
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

    int bc[256];
    int shift[m + 1];
    int border[m + 1];

    badChar(s, m, bc);
    goodSuffix(s, m, shift, border);

    for (int idx = 0; idx < W.NEff; idx++)
    {
        char* contentext[2] = { W.buffer[idx].web_url, W.buffer[idx].content };

        for (int t = 0; t < 2; t++) {
            char* text = contentext[t];
            int n = strlen(text);
            int i = m - 1;
            boolean found = false;

            while (i < n) {
                int j = m - 1;
                
                while (j >= 0) {
                    int pos = i - (m - 1 - j);
                    if (s[j] != text[pos]) break;
                    j--;
                }

                if (j < 0) {
                    printf("[%d] %s\n", idx+1,contentext[0]);
                    found = true;
                    break;

                    i += shift[0];
                } else {
                    int pos  = i - (m - 1 - j);
                    int bc_shift  = j - bc[(int)text[pos]];
                    if (bc_shift < 1) bc_shift = 1;
                    int gs_shift  = shift[j + 1];

                    if (bc_shift > gs_shift)
                        i += bc_shift;
                    else
                        i += gs_shift;
                }
                if(found) break;
            }
            if(found) break;
        }
    }
}