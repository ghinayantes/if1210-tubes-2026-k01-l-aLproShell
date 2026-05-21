#ifndef HISTORY_H
#define HISTORY_H

#include "boolean.h"
#include "stack.h"


void createTab(Page *P);

void bukaHalaman(Page *P, Webname New);

void back(Page *P, int langkah);

void forward(Page *P, int langkah);

void viewTabHistory(Page *P);

#endif