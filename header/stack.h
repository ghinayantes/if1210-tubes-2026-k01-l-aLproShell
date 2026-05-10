#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include "boolean.h"
#include <string.h>
#define MAX_CAPACITY 100
#define IDX_UNDEF -1

typedef struct {
    char url[100]; 
} Web;

typedef struct {
    Web buffer[MAX_CAPACITY];
    int idxTop;
} Stack;

typedef struct {
    Stack backHistory;
    Stack forwardHistory;
    Web currentTab;
    boolean Empty;
}Page;


void createStack(Stack *S);

int length(Stack S);

boolean isEmpty(Stack S);

boolean isFull(Stack S);

void push(Stack *S, Web W);

void pop(Stack *S, Web *W);

void createTab(Page *T);

void bukaHalaman(Page *T, Web New);

void back(Page *T);

void forward(Page *T);




#endif