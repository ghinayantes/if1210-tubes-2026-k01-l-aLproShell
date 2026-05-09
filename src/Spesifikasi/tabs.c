#include "../../header/tabs.h"
#include <stdio.h>
#include <string.h>

// konstruktor
void tabsListInit(TabsList *tl) {
    tl->count = 0;
    tl->currentIdx = 0;
    tl->tabCounter = 0;
 
    // Inisialisasi semua slot sebagai kosong 
    for (int i = 0; i < TABS_MAX_AMOUNT; i++) {
        tl->tabs[i].isUsed = false;
        tl->tabs[i].name[0] = '\0';
    }
 
    // Buat 1 tab default 
    tl->tabCounter++;
    snprintf(tl->tabs[0].name, TAB_NAME_LENGTH, "TAB%d", tl->tabCounter);
    tl->tabs[0].isUsed = true;
    tl->count = 1;
    tl->currentIdx = 0;
}

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

bool tabsListIsFull(const TabsList *tl) {
    return tl->count >= TABS_MAX_AMOUNT;
}

bool tabsListIsSingle(const TabsList *tl) {
    return tl->count == 1;
}

bool newTab(TabsList *tl) {
    if (tabsListIsFull(tl)) {
        return false;
    }
 
    tl->tabCounter++;
    snprintf(tl->tabs[tl->count].name, TAB_NAME_LENGTH, "TAB%d", tl->tabCounter);
    tl->tabs[tl->count].isUsed = true;
    tl->count++;
 
    return true;
}

bool closeTab(TabsList *tl) {
    if (tabsListIsSingle(tl)) {
        return false;
    }
 
    int cur = tl->currentIdx;
 
    // Geser semua tab setelah cur ke kiri 
    for (int i = cur; i < tl->count - 1; i++) {
        strncpy(tl->tabs[i].name, tl->tabs[i + 1].name, TAB_NAME_LENGTH);
        tl->tabs[i].isUsed = tl->tabs[i + 1].isUsed;
    }
 
    // Bersihkan slot terakhir 
    tl->tabs[tl->count - 1].isUsed  = false;
    tl->tabs[tl->count - 1].name[0] = '\0';
    tl->count--;
 
    // Jika tab yang ditutup adalah tab terakhir, mundur 1 
    if (tl->currentIdx >= tl->count) {
        tl->currentIdx = tl->count - 1;
    }
 
    return true;
}

bool nextTab(TabsList *tl, int n) {
    int dest = tl->currentIdx + n;
    if (dest < 0 || dest >= tl->count) {
        return false;
    }
    tl->currentIdx = dest;
    return true;
}
 
bool prevTab(TabsList *tl, int n) {
    int dest = tl->currentIdx - n;
    if (dest < 0 || dest >= tl->count) {
        return false;
    }
    tl->currentIdx = dest;
    return true;
}

void checkTab(const TabsList *tl) {
    printf("List of tab(s):\n");
    for (int i = 0; i < tl->count; i++) {
        printf("[%d] %s\n", i + 1, tl->tabs[i].name);
    }
    printf("Current tab: %s\n", tl->tabs[tl->currentIdx].name);
}
