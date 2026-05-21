#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "set.h" 
#include "boolean.h"

boolean LoadFromCSV(WebPages *W, const char *filepath);
boolean SaveToCSV(WebPages W, const char *filepath);

#endif