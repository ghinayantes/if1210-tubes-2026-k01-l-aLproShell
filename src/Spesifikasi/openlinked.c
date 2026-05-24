#include "openlinked.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int adj[100][100]; /*MATRIX YEAH CRAB RAVE*/


void deleteAdj(int del_idx, int NEff) {
    /*geser baris*/
    for (int i = del_idx; i < NEff - 1; i++) {
        for (int j = 0; j < 100; j++) {
            adj[i][j] = adj[i + 1][j];
        }
    }
    /*geser kolom*/
    for (int i = 0; i < 100; i++) {
        for (int j = del_idx; j < NEff - 1; j++) {
            adj[i][j] = adj[i][j + 1];
        }
    }
    for (int i = 0; i < 100; i++) {
        adj[NEff - 1][i] = 0;
        adj[i][NEff - 1] = 0;
    }
}

boolean SaveLinkedPages(WebPages *W, const char *filepath) {
    FILE *f = fopen(filepath, "w");
    if (!f) return false;

    fprintf(f, "id,id_sumber,id_tujuan\n");
    int link_id = 1;
    for (int i = 0; i < W->NEff; i++) {
        for (int j = 0; j < W->NEff; j++) {
            if (adj[i][j] == 1) {
                int src_id = W->buffer[i].id;
                int dst_id = W->buffer[j].id;
                fprintf(f, "%d,%d,%d\n", link_id, src_id, dst_id);
                link_id++;
            }
        }
    }
    fclose(f);
    return true;
}

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
            if (s != -1 && d != -1) {
                if (s< 100 && d <100) {
                    adj[s][d] = 1;
                } else {
                    printf("Kapasitas sudah penuh!");
                }
            }
        }
    }
    fclose(f);
    return true;
}

void displayLinkedPages(WebPages *W, int current_idx) {
    int local_linked_count = 0;
    for (int j = 0; j < W->NEff; j++) {
        if (adj[current_idx][j]) {
            if (local_linked_count == 0) printf("Linked pages:\n");
            local_linked_count++;
            printf("[%d] %s\n", local_linked_count, W->buffer[j].web_url);
        }
    }
}

void displayPage(WebPages *W, int idx) {
    printReal(W->buffer[idx].content);
    printf("\n");
    displayLinkedPages(W,idx);
}



void cmd_open(char *web_url, WebPages *W, Map *M, TabsList *TL) {
    int idx = findUrl(W, web_url);
    if (idx == -1) {
        printf("ERROR: HALAMAN '%s' TIDAK DITEMUKAN!\n", web_url);
        return;
    } 
    openpage(web_url, W,M, TL);
    displayLinkedPages(W, idx);
}

void openLinked(int x, WebPages *W, Map *M, TabsList *TL) {
    int aktif = TL->currentIdx;
    if (TL->tabs[aktif].tabHistory.Empty) {
        printf("ERROR: TIDAK ADA HALAMAN YANG SEDANG TERBUKA DI TAB INI!\n");
        return;
    }
    char *active_url = TL->tabs[aktif].tabHistory.currentTab.url; 
    int current_idx = findUrl(W, active_url);
    if (current_idx == -1) {
        printf("ERROR: HALAMAN SAAT INI TIDAK ADA DI DATABASE!\n");
        return;
    }
    int local_linked_count = 0;
    int target_page_idx = -1;
    int found = 0;
    for (int j = 0; j < W->NEff && !found; j++) {
        if (adj[current_idx][j]) { // adj is your adjacency matrix
            local_linked_count++;
            if (local_linked_count == x) {
                target_page_idx = j;
                found = 1;
            }
        }
    }
    if (target_page_idx == -1) {
        printf("ERROR: INDEKS TIDAK VALID! (Hanya ada %d tautan)\n", local_linked_count);
        return;
    }
    char *target_url = W->buffer[target_page_idx].web_url;
    cmd_open(target_url, W, M, TL);
}
