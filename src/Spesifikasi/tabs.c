#include "tabs.h"
#include <stdio.h>
#include <string.h>

// selektor
int countTabs(const TabsList *tl) {
    return tl->count;
}

int currentTabIdx(const TabsList *tl) {
    return tl->currentIdx;
}

void currentTabName(const TabsList *tl, TabName out) {
    strncpy(out, tl->tabs[tl->currentIdx].name, TAB_NAME_LENGTH);
}

void tabsGetNameAt(const TabsList *tl, int idx, TabName out) {
    strncpy(out, tl->tabs[idx].name, TAB_NAME_LENGTH);
}

boolean tabsListIsFull(const TabsList *tl) {
    return tl->count >= TABS_MAX_AMOUNT;
}

boolean tabsListIsSingle(const TabsList *tl) {
    return tl->count == 1;
}

boolean newTab(TabsList *tl) {
    if (tabsListIsFull(tl)) {
        printf("ERROR: Jumlah tab tidak bisa melebihi batas maksimum!\n");
        return false;
    }
 
    tl->tabCounter++;
    snprintf(tl->tabs[tl->count].name, TAB_NAME_LENGTH, "TAB%d", tl->tabCounter);
    tl->tabs[tl->count].isUsed = true;
    createTab(&(tl->tabs[tl->count].tabHistory));
 
    printf("Tab baru (TAB%d) berhasil dibuat!\n", tl->tabCounter);
    tl->count++;
 
    return true;
}

boolean closeTab(TabsList *tl) {
    if (tabsListIsSingle(tl)) {
        printf("ERROR: Tidak bisa menutup tab, tab minimal berjumlah 1!\n");
        return false;
    }
 
    int cur = tl->currentIdx;
    TabName closedName;
    strncpy(closedName, tl->tabs[cur].name, TAB_NAME_LENGTH);
 
    // Geser semua tab setelah cur ke kiri 
    for (int i = cur; i < tl->count - 1; i++) {
        strncpy(tl->tabs[i].name, tl->tabs[i + 1].name, TAB_NAME_LENGTH);
        tl->tabs[i].isUsed     = tl->tabs[i + 1].isUsed;
        tl->tabs[i].tabHistory = tl->tabs[i + 1].tabHistory;
    }
 
    // Bersihkan slot terakhir 
    tl->tabs[tl->count - 1].isUsed  = false;
    tl->tabs[tl->count - 1].name[0] = '\0';
    tl->count--;
 
    // Jika tab yang ditutup adalah tab terakhir, mundur 1 
    if (tl->currentIdx >= tl->count) {
        tl->currentIdx = tl->count - 1;
    }
    
    printf("%s berhasil ditutup.\n", closedName);
    return true;
}

boolean nextTab(TabsList *tl, int n) {
    if (n < 0 || n > 999999) {
    printf("Masukan tidak valid.\n");
    return false;
    }

    int dest = tl->currentIdx + n;
    if (dest < 0 || dest >= tl->count) {
        printf("ERROR: Posisi tab tidak valid!\n");
        return false;
    }

    tl->currentIdx = dest;
    printf("Tab saat ini berhasil diganti ke %s.\n", tl->tabs[tl->currentIdx].name);
    return true;
}
 
boolean prevTab(TabsList *tl, int n) {
    if (n < 0 || n > 999999) {
    printf("Masukan tidak valid.\n");
    return false;
    }

    int dest = tl->currentIdx - n;
    if (dest < 0 || dest >= tl->count) {
        printf("ERROR: Posisi tab tidak valid!\n");
        return false;
    }

    tl->currentIdx = dest;
    printf("Tab saat ini berhasil diganti ke %s.\n", tl->tabs[tl->currentIdx].name);
    return true;
}

void checkTab(const TabsList *tl) {
   printf("List of tab(s):\n");
    for (int i = 0; i < tl->count; i++) {
        printf("[%d] %s\n", i + 1, tl->tabs[i].name);
    }
    printf("Current tab: %s\n", tl->tabs[tl->currentIdx].name);
}
