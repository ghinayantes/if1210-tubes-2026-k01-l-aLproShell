#ifndef QUEUE_H
#define QUEUE_H

#include "config.h"
#define URL_MAX_LENGTH 256

#include "url.h"

typedef struct {
    URL url; 
    int ticksLeft; 
    int ticksTotal; 
} DownloadItem;

typedef struct {
    DownloadItem items[DOWNLOAD_MAX_AMOUNT]; 
    int head; 
    int tail; 
    int count; 
} DownloadQueue;

// konstruktor
void DownloadQueueInit(DownloadQueue *dq); 

#endif