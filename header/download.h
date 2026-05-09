#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "boolean.h"

#define DOWNLOAD_MAX_AMOUNT 5
#define URL_MAX_LENGTH 256

typedef char URL[URL_MAX_LENGTH];

typedef struct {
    URL url; // URL halaman yang akan diunduh 
    int ticksLeft; // Sisa ticks yang dibutuhkan untuk selesai 
    int ticksTotal; // Total ticks awal (untuk info) 
} DownloadItem;

typedef struct {
    DownloadItem items[DOWNLOAD_MAX_AMOUNT]; // Array queue 
    int head; // Indeks elemen terdepan 
    int tail; // Indeks slot kosong berikutnya 
    int count; // Jumlah item dalam antrian 
} DownloadQueue;

// helper
int DownloadCalcTicks(const char *url); // Menghitung ticks yang dibutuhkan untuk URL tertentu

// konstruktor
void DownloadQueueInit(DownloadQueue *dq); // Membuat DownloadQueue kosong

// selektor
int  DownloadCount(const DownloadQueue *dq); // Mengembalikan jumlah item dalam antrian

bool DownloadIsEmpty(const DownloadQueue *dq); // Mengembalikan true jika antrian kosong

bool DownloadIsFull(const DownloadQueue *dq); // Mengembalikan true jika antrian penuh

void DownloadCurrentURL(const DownloadQueue *dq, URL out); // Mengisi out dengan URL yang sedang diunduh, antrian tidak kosong

int  DownloadCurrentTicksLeft(const DownloadQueue *dq); // Mengembalikan sisa ticks dari item yang sedang diunduh, antrian tidak kosong

// operasi utama
bool IsURLValid(const char *url); 
/* Mengembalikan true jika URL memenuhi spesifikasi E01:
   - Tidak diawali '-'
   - Panjang label 1-63 karakter (huruf, angka, '-')
   - Tidak diakhiri '-' sebelum titik
   - Memiliki suffix minimal 2 karakter alfabet */
   
bool DownloadQueueDownload(DownloadQueue *dq, const char *url); // Menambahkan URL ke antrian unduhan
/* Ticks dihitung otomatis dari panjang URL.
   Mengembalikan false jika antrian sudah penuh */

bool DownloadTick(DownloadQueue *dq);
/* tick: Memajukan waktu sistem sebanyak 1 langkah.
   - Jika antrian kosong, cetak pesan kosong.
   - Mengurangi ticksLeft item terdepan sebesar 1.
   - Jika ticksLeft mencapai 0, unduhan selesai:
     - Simpan file <URL>.txt (postfix domain dipotong)
     - Dequeue item tersebut
     - Lanjutkan ke item berikutnya jika ada.
   Mengembalikan true jika ada item yang selesai diunduh saat tick ini. */

void DownloadQueueStripExtension(const char *url, char *out); // Memotong postfix URL, hasil disimpan ke out

#endif