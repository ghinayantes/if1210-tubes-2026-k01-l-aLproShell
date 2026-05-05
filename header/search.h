#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <string.h>

#include "set.h"

void badChar(char* s, int len, int bc[]);

void goodSuffix(char* s, int len, int shift[], int b[]);

void boyerMoore(char* s, WebPages W);

#endif