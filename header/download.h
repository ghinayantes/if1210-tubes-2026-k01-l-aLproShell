#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "boolean.h"

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

// helper
int DownloadCalcTicks(const char *url); 

// konstruktor
void DownloadQueueInit(DownloadQueue *dq); 

// selektor
int  DownloadCount(const DownloadQueue *dq); 

boolean DownloadIsEmpty(const DownloadQueue *dq); 

boolean DownloadIsFull(const DownloadQueue *dq); 

void DownloadCurrentURL(const DownloadQueue *dq, URL out); 

int  DownloadCurrentTicksLeft(const DownloadQueue *dq); 

// operasi utama
boolean IsURLValid(const char *url); // E01
   
boolean DownloadQueueDownload(DownloadQueue *dq, const char *url); 

boolean DownloadTick(DownloadQueue *dq);

void DownloadQueueStripExtension(const char *url, char *out); 

#endif
