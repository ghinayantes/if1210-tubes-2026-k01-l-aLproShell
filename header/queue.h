#ifndef QUEUE_H
#define QUEUE_H

#define DOWNLOAD_MAX_AMOUNT 5
#define URL_MAX_LENGTH 256

typedef char URL[URL_MAX_LENGTH];

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