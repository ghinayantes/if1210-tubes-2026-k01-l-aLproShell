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
    return (S.idxTop == MAX_CAPACITY-1);
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
void createTab(Page *T){
    createStack(&(T->backHistory));
    createStack(&(T->forwardHistory));
    T->Empty = true;
}

void bukaHalaman(Page *T,Web New){
    if (T->Empty == false){
        push(&(T->backHistory), T->currentTab);
    }
    T->currentTab = New;
    T->Empty = false;
    createStack(&(T->forwardHistory));
}

void back(Page *T){
    if (T->Empty){ // Kasus 1
        printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!");
    } else if (isEmpty(T->backHistory)){ // Kasus 2
        printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!");
    } else{         // Kasus 3
        push(&(T->forwardHistory),T->currentTab);
        pop(&(T->backHistory),&(T->currentTab));
    }
}

void forward(Page *T){
    if (T->Empty){
        printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!");
    } else if (isEmpty(T->forwardHistory)){
        printf("ERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!");
    } else{
        push(&(T->backHistory),T->currentTab);
        pop(&(T->forwardHistory),&(T->currentTab));
    }
}




