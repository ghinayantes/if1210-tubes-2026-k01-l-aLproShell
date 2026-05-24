#ifndef OPENLINKED_H
#define OPENLINKED_H
#include "openpage.h"
#include "set.h" 
#include "boolean.h"

extern int adj[100][100];

int findUrl(WebPages *W, char *web_url);
int findId(WebPages *W, int id);
boolean LoadLinkedPages(WebPages *W, const char *filepath);
void displayLinkedPages(WebPages *W, int idx);
void displayPage(WebPages *W, int idx);

void cmd_open(char *web_url, WebPages *W, Map *M, TabsList *TL);
void openLinked(int x, WebPages *W, Map *M, TabsList *TL);

#endif