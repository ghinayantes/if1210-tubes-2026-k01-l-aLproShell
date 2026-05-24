#ifndef TABS_H
#define TABS_H

#include "list.h"

// selektor 
int countTabs(const TabsList *tl); // jumlah tab saat ini

int currentTabIdx(const TabsList *tl); // indeks current tab

void currentTabName(const TabsList *tl, TabName out); // nama current tab

void tabsGetNameAt(const TabsList *tl, int idx, TabName out); // nama tab pada indeks idx, out = nama tersebut

boolean tabsListIsFull(const TabsList *tl); 

boolean tabsListIsSingle(const TabsList *tl);

boolean newTab(TabsList *tl); // tambah tab di akhir list, false jika penuh

boolean closeTab(TabsList *tl); // menutup current tab, tab pindah ke sebelumnya, false jika hanya ada 1 tab

boolean nextTab(TabsList *tl, int n); // Berpindah ke tab sebanyak n posisi ke kanan dari current

boolean prevTab(TabsList *tl, int n); // Berpindah ke tab sebanyak n posisi ke kiri dari current

void checkTab(const TabsList *tl); // Mencetak seluruh daftar tab dan current tab



#endif
