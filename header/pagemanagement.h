#ifndef PAGEMANAGEMENT_H
#define PAGEMANAGEMENT_H

#include "master.h"

void runAddPage(WebPages *W, char* s);
void runDeletePage(WebPages *W, Map *M, char* s, const char *pages_folder, const char *links_filepath);
void runEditPage(WebPages *W, Map *M, char* s, const char *pages_folder);

#endif