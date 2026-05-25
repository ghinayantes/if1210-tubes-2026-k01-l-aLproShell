#include "prioqueue.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void CreateGlobalHistory(GlobalHistory *pq) {
    pq->size = 0;
}

boolean IsEmptyGlobal(GlobalHistory pq) {
    return pq.size == 0;
}

boolean IsFullGlobal(GlobalHistory pq) {
    return pq.size == HISTORY_MAX_AMOUNT;
}

boolean isInQueueGlobal(GlobalHistory pq, URL url) {
    if (IsEmptyGlobal(pq)) return false;
    
    for (int i = 0; i < pq.size; i++)
    {
        if(strcmp(pq.buffer[i].url, url) == 0) return true;
    }
    return false;
}

void EnqueueGlobal(GlobalHistory *pq, ElType val) {
    int found = -1;

    for (int i = 0; i < pq->size && found == -1; i++) 
    {
        if(strcmp(pq->buffer[i].url, val.url) == 0) found = i;
    }

    val.visited = (int)time(NULL); 

    if(found != -1){
        for (int i = found; i < pq->size - 1; i++) 
        {
            pq->buffer[i] = pq->buffer[i + 1];
        }
        pq->buffer[pq->size - 1] = val;
    } 
    else{
        if(IsFullGlobal(*pq)){
            for (int i = 0; i < HISTORY_MAX_AMOUNT - 1; i++) 
            {
                pq->buffer[i] = pq->buffer[i + 1];
            }
            pq->buffer[HISTORY_MAX_AMOUNT - 1] = val;
        } 
        else {
            pq->buffer[pq->size] = val;
            pq->size++;
        }
    }
}

void DequeueGlobal(GlobalHistory *pq, ElType *val) {
    if (!IsEmptyGlobal(*pq)) {
        *val = pq->buffer[0];
        
        for(int i = 0; i < pq->size - 1; i++) 
        {
            pq->buffer[i] = pq->buffer[i + 1];
        }
        
        pq->size--;
    }
}

void DisplayHistory(GlobalHistory pq) {
    printf("Riwayat halaman yang pernah dikunjungi:\n");
    
    if(IsEmptyGlobal(pq)){
        printf("(Belum ada riwayat kunjungan)\n");
        return;
    }

    int displayIndex = 1;
    for (int i = pq.size - 1; i >= 0; i--) 
    {
        time_t time = (time_t)pq.buffer[i].visited;
        struct tm *timeInfo = localtime(&time);

        printf("[%d] %s (%02d:%02d)\n", displayIndex, pq.buffer[i].url, timeInfo->tm_hour, timeInfo->tm_min);
        displayIndex++;
    }
}