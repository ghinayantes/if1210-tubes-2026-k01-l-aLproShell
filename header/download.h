#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "boolean.h"
#include "queue.h"

// helper
int DownloadCalcTicks(const char *url); 

// selektor
int  DownloadCount(const DownloadQueue *dq); 

boolean DownloadIsEmpty(const DownloadQueue *dq); 

boolean DownloadIsFull(const DownloadQueue *dq); 

void DownloadCurrentURL(const DownloadQueue *dq, URL out); 

void LookupWebPageContent(const char *url, char *out, int outSize);

int  DownloadCurrentTicksLeft(const DownloadQueue *dq); 

// operasi utama
boolean IsURLValid(const char *url); // E01
   
boolean DownloadQueueDownload(DownloadQueue *dq, const char *url); 

boolean DownloadTick(DownloadQueue *dq);

void DownloadQueueStripExtension(const char *url, char *out); 

#endif
