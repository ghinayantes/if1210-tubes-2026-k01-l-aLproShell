#include "queue.h"
#include <stdio.h>

// konstruktor
void DownloadQueueInit(DownloadQueue *dq) {
    dq->head = 0;
    dq->tail = 0;
    dq->count = 0;
    for (int i = 0; i < DOWNLOAD_MAX_AMOUNT; i++) {
        dq->items[i].url[0] = '\0';
        dq->items[i].ticksLeft = 0;
        dq->items[i].ticksTotal = 0;
    }
}