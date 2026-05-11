#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include "boolean.h"
#include <string.h>
#define MAX_WEB 100
#define IDX_UNDEF -1

typedef struct {
    char url[100]; 
} Webname;

typedef struct {
    Webname buffer[MAX_WEB];
    int idxTop;
} Stack;

typedef struct {
    Stack backHistory;
    Stack forwardHistory;
    Webname currentTab;
    boolean Empty;
}Page;


void createStack(Stack *S);

int length(Stack S);

boolean isStackEmpty(Stack S);

boolean isStackFull(Stack S);

void push(Stack *S, Webname W);

void pop(Stack *S, Webname *W);

void createTab(Page *P);

void bukaHalaman(Page *P, Webname New);

void back(Page *P, int langkah);

void forward(Page *P, int langkah);

void viewTabHistory(Page P);




#endif