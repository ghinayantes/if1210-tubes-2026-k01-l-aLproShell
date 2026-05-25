#ifndef GlobalHistory_H
#define GlobalHistory_H

#define HISTORY_MAX_AMOUNT 10

#include "boolean.h"
#include "url.h"

typedef struct {
    URL url;
    int visited; 
} UrlHistory;

typedef UrlHistory ElType;

typedef struct {
    ElType buffer[HISTORY_MAX_AMOUNT];
    int size; 
} GlobalHistory;

void CreateGlobalHistory(GlobalHistory *pq);

boolean IsEmptyGlobal(GlobalHistory pq);

boolean IsFullGlobal(GlobalHistory pq);

boolean isInQueueGlobal(GlobalHistory pq, URL url);

void EnqueueGlobal(GlobalHistory *pq, ElType val);

void DequeueGlobal(GlobalHistory *pq, ElType *val);

void DisplayHistory(GlobalHistory pq);

#endif