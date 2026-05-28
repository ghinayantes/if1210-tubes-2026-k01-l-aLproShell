#ifndef LIST_H
#define LIST_H

#include "boolean.h"
#include "history.h"

#include "config.h"
#define TAB_NAME_LENGTH 20

typedef char TabName[TAB_NAME_LENGTH];

typedef struct {
    TabName name;
    boolean isUsed;
    Page tabHistory;
} Tab;

typedef struct {
    Tab tabs[TABS_MAX_AMOUNT];
    int count; // jumlah tab aktif
    int currentIdx; // indeks tab aktif
    int tabCounter; // counter nama tab
} TabsList;

// konstruktor  
void tabsListInit(TabsList *tl); // Membuat TabsList baru dengan 1 tab default (TAB1). Current tab diset ke tab pertama.

#endif