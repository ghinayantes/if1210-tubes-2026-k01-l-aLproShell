#ifndef OPENPAGE_H
#define OPENPAGE_H

#include <stdio.h>
#include <string.h>

#include "set.h"
#include "map.h"
#include "tabs.h"

void openpage(char* s, WebPages *W, Map *M);
void openpage(char* s, WebPages *W, Map *M, TabsList *TL);

#endif