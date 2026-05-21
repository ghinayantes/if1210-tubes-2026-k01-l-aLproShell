#include "history.h"
#include <stdio.h>

void createTab(Page *P){
    createStack(&(P->backHistory));
    createStack(&(P->forwardHistory));
    P->Empty = true;
}

void bukaHalaman(Page *P,Webname New){
    if (P->Empty == false){
        push(&(P->backHistory), P->currentTab);
    }
    P->currentTab = New;
    P->Empty = false;
    createStack(&(P->forwardHistory));
}

void back(Page *P, int langkah){
    if (langkah < 1 || langkah > 999999){
        printf("Input tidak valid\n");
    } else {
        if (P->Empty){ 
            printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!\n");
        } else if (isStackEmpty(P->backHistory)){ 
            printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!\n");
        } else {
            while (langkah > 0 && !isStackEmpty(P->backHistory)){
                push(&(P->forwardHistory), P->currentTab);
                pop(&(P->backHistory), &(P->currentTab));
                langkah--;
            }
            printf("BACK: KEMBALI KE HALAMAN %s\n", P->currentTab.url);
        }
    }
}

void forward(Page *P, int langkah){
    if (langkah < 1 || langkah > 999999){
        printf("Input tidak valid\n");
    } else {
        if (P->Empty){
            printf("ERROR: FORWARD TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SELANJUTNYA!\n");
        } else if (isStackEmpty(P->forwardHistory)){
            printf("ERROR: FORWARD TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SELANJUTNYA!\n");
        } else {
            while(langkah > 0 && !isStackEmpty(P->forwardHistory)) {
                push(&(P->backHistory), P->currentTab);
                pop(&(P->forwardHistory), &(P->currentTab));
                langkah--;
            }
            printf("FORWARD: KEMBALI KE HALAMAN %s\n", P->currentTab.url);
        }
    }
}

void viewTabHistory(Page *P){
    if (P->Empty){
        printf("Anda belum membuka tab manapun\n");
    } else {
        int number = 1;
        //Menampilkan history sebelum posisi web saat ini
        for(int i = 0; i <= P->backHistory.idxTop; i++){
            printf("[%d] %s\n", number, P->backHistory.buffer[i].url); 
            number++;
        }
        //Menampilkan posisi history web saat ini
        printf("[%d] %s <- YOU ARE HERE\n", number, P->currentTab.url);
        number++;
        //Menampilkan history setelah posisi web saat ini
        for(int i = P->forwardHistory.idxTop; i >= 0; i--){
            printf("[%d] %s\n", number, P->forwardHistory.buffer[i].url); 
            number++;
        }
    }
}
