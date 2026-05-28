#include "openpage.h"

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


void openpage(char* s, WebPages *W, Map *M, TabsList *TL, GlobalHistory *PQ){
    char* val = getMap(s, M);
    if (val != NULL) {
        printf("[Status: Cache-Hit] Mengambil data dari cache...\n\n");
        printReal(val);
        printf("\n");

        Webname webBaru;
        strcpy(webBaru.url, s);
        int aktif = TL->currentIdx;
        UrlHistory page;
        strcpy(page.url, s);
        EnqueueGlobal(PQ, page);
        bukaHalaman(&(TL->tabs[aktif].tabHistory), webBaru);
    } 
    else {
        printf("[Status: Cache-Miss] Mengambil data dari database...\n\n");
        val = getWeb(s, W);
        if (val != NULL) {
            printReal(val);
            printf("\n");
            setMap(s, val, M);
            Webname webBaru;
            strcpy(webBaru.url, s);
            int aktif = TL->currentIdx;
            UrlHistory page;
            strcpy(page.url, s);
            EnqueueGlobal(PQ, page);
            bukaHalaman(&(TL->tabs[aktif].tabHistory), webBaru);
        } else {
            printf("Tidak ada Website\n");
        }
    }
}