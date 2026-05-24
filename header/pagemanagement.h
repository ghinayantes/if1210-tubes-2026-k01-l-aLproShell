#ifndef PAGEMANAGEMENT_H
#define PAGEMANAGEMENT_H

#include <stdio.h>
#include <string.h>
#include "set.h"
#include "map.h"

void runAddPage(WebPages *W, char* s);
void runDeletePage(WebPages *W, Map *M, char* s);
void runEditPage(WebPages *W, Map *M, char* s);

#endif