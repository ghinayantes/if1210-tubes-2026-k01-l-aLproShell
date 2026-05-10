#include "../../header/stack.h"


void createStack(Stack *S){
    S->idxTop = IDX_UNDEF;
    
}

int length(Stack S){
    return S.idxTop+1;
}

boolean isEmpty(Stack S){
    return (S.idxTop == IDX_UNDEF);
}

boolean isFull(Stack S){
    return (S.idxTop == MAX_WEB-1);
}

void push (Stack *S, Web W){
    if (!isFull(*S)) {
        S->idxTop++;
        S->buffer[S->idxTop] = W;
    } else {
        printf("Gagal push: History sudah penuh!\n");
    }
}

void pop(Stack *S, Web *W){
    if (!isEmpty(*S)) {
        *W = S->buffer[S->idxTop];
        S->idxTop--;
    } else {
        printf("Gagal pop: History kosong!\n");
    }
}
void createTab(Page *P){
    createStack(&(P->backHistory));
    createStack(&(P->forwardHistory));
    P->Empty = true;
}

void bukaHalaman(Page *P,Web New){
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
        } else if (isEmpty(P->backHistory)){ 
            printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!\n");
        } else {

            while (langkah > 0 && !isEmpty(P->backHistory)){
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
        } else if (isEmpty(P->forwardHistory)){
            printf("ERROR: FORWARD TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SELANJUTNYA!\n");
        } else {
            while(langkah > 0 && !isEmpty(P->forwardHistory)) {
                push(&(P->backHistory), P->currentTab);
                pop(&(P->forwardHistory), &(P->currentTab));
                langkah--;
            }
            printf("FORWARD: KEMBALI KE HALAMAN %s\n", P->currentTab.url);
        }
    }
}

void viewTabHistory(Page P){
    if (P.Empty){
        printf("Anda belum membuka tab manapun\n");
    } else {
        int number = 0;
        for(int i = 0; i <= P.backHistory.idxTop; i++){
            printf("[%d] %s\n", number, P.backHistory.buffer[i].url); 
            number++;
        }
        printf("[%d] %s <- YOU ARE HERE\n", number, P.currentTab.url);
        number++;
        for(int i = P.forwardHistory.idxTop; i >= 0; i--){
            printf("[%d] %s\n", number, P.forwardHistory.buffer[i].url); 
            number++;
        }
    }
}

