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



