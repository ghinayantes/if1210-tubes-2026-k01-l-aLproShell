#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "set.h" 
#include "list.h"
#include "boolean.h"

#include "config.h"

boolean LoadFromCSV(WebPages *W, const char *filepath);
boolean SaveToCSV(WebPages W, const char *filepath);
void loadAgain(const char *path, char *out);
boolean loadData(WebPages *W);

boolean LoadConfig(TabsList *TL, const char *filepath);
boolean SaveConfig(const TabsList *TL, const char *folder);

#endif