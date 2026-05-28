#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "set.h" 
#include "list.h"
#include "prioqueue.h"
#include "boolean.h"

#include "config.h"

boolean LoadFromCSV(WebPages *W, const char *filepath);
boolean SaveToCSV(WebPages W, const char *filepath);
void loadAgain(const char *path, char *out);
boolean loadData(WebPages *W);

boolean LoadConfig(TabsList *TL, GlobalHistory *PQ, const char *filepath);
boolean SaveConfig(const TabsList *TL, const GlobalHistory *PQ, const char *folder);

#endif