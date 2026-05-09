#include "../../header/openpage.h"
#include <stdio.h>

void printReal(char *str){
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && str[i+1] == 'n') {
            printf("\n");
            i++;
        } else {
            putchar(str[i]);
        }
    }
}

void openpage(char* s, WebPages *W, Map *M){
    char* val = getMap(s, M);
    if (val != NULL) {
        printf("[Status: Cache-Hit] Mengambil data dari cache...\n");
        printReal(val);
        printf("\n");
    } 
    else {
        printf("[Status: Cache-Miss] Mengambil data dari database...\n");
        val = getWeb(s, W);
        if (val != NULL) {
            printReal(val);
            printf("\n");
            setMap(s, val, M);
        } else {
            printf("Tidak ada Website\n");
        }
    }
}