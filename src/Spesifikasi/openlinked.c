#include "openlinked.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int findUrl(WebPages *W, char *web_url) {
    for (int i = 0; i < W->NEff; i++)
        if (strcmp(W->buffer[i].web_url, web_url) == 0) return i;
    return -1;
}

int findId(WebPages *W, int id) {
    for (int i = 0; i < W->NEff; i++)
        if (W->buffer[i].id == id) return i;
    return -1;
}


boolean LoadLinkedPages(WebPages *W, const char *filepath) {
    FILE *f = fopen(filepath, "r");
    if (!f) return false;
    memset(adj, 0, sizeof(adj));
    char line[100];
    fgets(line, sizeof(line), f); /* skip header */
    while (fgets(line, sizeof(line), f)) {
        int id, src_id, dst_id;
        if (sscanf(line, "%d,%d,%d", &id, &src_id, &dst_id) == 3) {
            int s = findId(W, src_id);
            int d = findId(W, dst_id);
            if (s != -1 && d != -1) adj[s][d] = 1;
        }
    }
    fclose(f);
    return true;
}

void displayLinkedPages(WebPages *W, int idx) {
    linked_count = 0;
    for (int j = 0; j < W->NEff; j++)
        if (adj[idx][j]) linked_buf[linked_count++] = j;
    if (linked_count > 0) {
        printf("Linked pages:\n");
        for (int i = 0; i < linked_count; i++)
            printf("[%d] %s\n", i + 1, W->buffer[linked_buf[i]].web_url);
    }
}

void displayPage(WebPages *W, int idx) {
    printReal(W->buffer[idx].content);
    printf("\n");
    displayLinkedPages(W,idx);
}



void cmd_open(char *web_url, WebPages *W, Map *M) {
    int idx = findUrl(W, web_url);
    if (idx == -1) {
        printf("ERROR: HALAMAN '%s' TIDAK DITEMUKAN!\n", web_url);
        return;
    } 
    current_page = idx;
    linked_count = 0;
    openpage(web_url, W,M);
    displayLinkedPages(W, idx);
}

void openLinked(int x, WebPages *W) {
    if (current_page == -1) {
        printf("ERROR: COMMAND HANYA DAPAT DIGUNAKAN SAAT HALAMAN WEB TERBUKA!\n");
        return;
    }
    if (linked_count == 0) {
        printf("ERROR: HALAMAN TIDAK MEMILIKI TAUTAN YANG BISA DIBUKA!\n");
        displayPage(W, current_page);
        return;
    }
    if (x < 1 || x > linked_count) {
        printf("ERROR: INDEKS TIDAK VALID! (1 - %d)\n", linked_count);
        return;
    }
    current_page = linked_buf[x - 1];
    linked_count = 0;
    displayPage(W, current_page);
}
