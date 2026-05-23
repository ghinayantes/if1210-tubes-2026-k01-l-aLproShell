#ifndef DISCOVER_H
#define DISCOVER_H

#include <stdio.h>
#include <string.h>

#include "set.h"

unsigned int lcg(unsigned int current_seed);

void runDiscover(WebPages *W, unsigned int *seed);

#endif