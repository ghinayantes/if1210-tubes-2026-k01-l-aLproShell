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

void createStack(Stack *S);

int length(Stack S);

boolean isEmpty(Stack S);

boolean isFull(Stack S);

void push (Stack *S, Web W);

void pop(Stack *S, Web W);



#endif