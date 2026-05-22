#ifndef PAGEMANAGEMENT_H
#define PAGEMANAGEMENT_H

#include <stdio.h>
#include <string.h>
#include "set.h"

void runAddPage(WebPages *W, char* s);
void runDeletePage(WebPages *W, char* s);
void runEditPage(WebPages *W, char* s);

#endif