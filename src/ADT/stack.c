#include "stack.h"


void createStack(Stack *S){
    S->idxTop = IDX_UNDEF;
    
}

int length(Stack S){
    return S.idxTop+1;
}

boolean isStackEmpty(Stack S){
    return (S.idxTop == IDX_UNDEF);
}

boolean isStackFull(Stack S){
    return (S.idxTop == MAX_WEB-1);
}

void push (Stack *S, Webname W){
    if (!isStackFull(*S)) {
        S->idxTop++;
        S->buffer[S->idxTop] = W;
    } else {
        printf("Gagal push: History sudah penuh!\n");
    }
}

void pop(Stack *S, Webname *W){
    if (!isStackEmpty(*S)) {
        *W = S->buffer[S->idxTop];
        S->idxTop--;
    } else {
        printf("Gagal pop: History kosong!\n");
    }
}


