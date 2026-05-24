#include <stdio.h>
#include <string.h>
#include <math.h>

#include "download.h"

// fungsi helper
boolean isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9');
}

boolean isAlphabet(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z');
}

int DownloadCalcTicks(const char *url) {
    int len = (int)strlen(url);
    return (len / 5) + 2; 
}

void DownloadQueueStripExtension(const char *url, char *out) {
    strncpy(out, url, URL_MAX_LENGTH - 1);
    out[URL_MAX_LENGTH - 1] = '\0';
 
    // Cari titik terakhir dan potong 
    char *dot = strrchr(out, '.');
    if (dot != NULL) {
        *dot = '\0';
    }
}

int DownloadCount(const DownloadQueue *dq) {
    return dq->count;
}
 
boolean DownloadIsEmpty(const DownloadQueue *dq) {
    return dq->count == 0;
}

boolean DownloadIsFull(const DownloadQueue *dq) {
    return dq->count >= DOWNLOAD_MAX_AMOUNT;
}
 
void DownloadCurrentURL(const DownloadQueue *dq, URL out) {
    strncpy(out, dq->items[dq->head].url, URL_MAX_LENGTH);
}
 
int DownloadCurrentTicksLeft(const DownloadQueue *dq) {
    return dq->items[dq->head].ticksLeft;
}

// operasi utama
boolean IsURLValid(const char *url) {
    int len = strlen(url);
    if (len == 0) return false;

    // Cek karakter pertama
    if (url[0] == '-') return false;

    // Cari posisi titik pertama 
    const char *firstDot = strchr(url, '.');
    if (firstDot == NULL) return false; 

    int labelLen = firstDot - url;

    // Cek panjang label
    if (labelLen < 1 || labelLen > 63) return false;

    // Cek karakter sebelum titik
    if (*(firstDot - 1) == '-') return false;

    // Validasi isi label 
    for (int i = 0; i < labelLen; i++) {
        if (!isAlphanumeric(url[i]) && url[i] != '-') {
            return false; 
        }
    }

    // Validasi Suffix 
    const char *lastDot = strrchr(url, '.');
    int suffixLen = strlen(lastDot + 1);

    if (suffixLen < 2) return false; 

    for (int i = 1; i <= suffixLen; i++) {
        if (!isAlphabet(lastDot[i])) {
            return false; 
        }
    }

    return true;
}

boolean DownloadQueueDownload(DownloadQueue *dq, const char *url) { 
    if (!IsURLValid(url)) {
        printf("Masukan tidak valid.\n"); 
        return false;
    }

    if (DownloadIsFull(dq)) {
        return false;
    }

    int ticks = DownloadCalcTicks(url);
    int pos = (dq->head + dq->count) % DOWNLOAD_MAX_AMOUNT;

    strncpy(dq->items[pos].url, url, URL_MAX_LENGTH - 1);
    dq->items[pos].url[URL_MAX_LENGTH - 1] = '\0';
    dq->items[pos].ticksLeft = ticks;
    dq->items[pos].ticksTotal = ticks;
    dq->count++;

    if (dq->count == 1) {
        printf("Download %s (%d ticks)\n", url, ticks);
    } 
    else {
        int headTicksLeft = dq->items[dq->head].ticksLeft;
        printf("Download %s (%d ticks) -> antrian no %d, %d ticks masih tertunda dari antrian sebelumnya\n", url, ticks, dq->count, headTicksLeft);
    }

    return true;
}

boolean DownloadTick(DownloadQueue *dq) {
    if (DownloadIsEmpty(dq)) {
        printf("Antrian download saat ini kosong.\n");
        return false;
    }
 
    dq->items[dq->head].ticksLeft--;
 
    if (dq->items[dq->head].ticksLeft > 0) {
        printf("Downloading %s... (%d ticks tersisa)\n", dq->items[dq->head].url, dq->items[dq->head].ticksLeft);
        return false;
    }
 
    // Unduhan selesai 
    URL finishedURL;
    char stripped[URL_MAX_LENGTH];
 
    strncpy(finishedURL, dq->items[dq->head].url, URL_MAX_LENGTH);
    DownloadQueueStripExtension(finishedURL, stripped);
 
    // Simpan file <stripped>.txt 
    char filename[URL_MAX_LENGTH + 4];
    snprintf(filename, sizeof(filename), "%s.txt", stripped);
 
    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        fprintf(f, "Konten halaman: %s\n", finishedURL);
        fclose(f);
    }
 
    printf("%s selesai didownload, ke file %s.txt.\n", finishedURL, stripped);
 
    dq->items[dq->head].url[0] = '\0';
    dq->items[dq->head].ticksLeft = 0;
    dq->items[dq->head].ticksTotal = 0;
    dq->head = (dq->head + 1) % DOWNLOAD_MAX_AMOUNT;
    dq->count--;
 
    if (!DownloadIsEmpty(dq)) {
        printf("Lanjut downloading %s... (%d ticks tersisa)\n",
               dq->items[dq->head].url,
               dq->items[dq->head].ticksLeft);
    }
 
    return true;
}
