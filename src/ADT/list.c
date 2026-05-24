#include "list.h"
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
    createTab(&(tl->tabs[0].tabHistory));
    tl->count = 1;
    tl->currentIdx = 0;
}