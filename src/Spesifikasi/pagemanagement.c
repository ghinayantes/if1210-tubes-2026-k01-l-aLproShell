#include "../../header/pagemanagement.h"
#include "../../header/openlinked.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getMaxPageId(WebPages *W) {
    int max_id = 0;
    for (int i = 0; i < W->NEff; i++) {
        if (W->buffer[i].id > max_id) {
            max_id = W->buffer[i].id;
        }
    }
    return max_id;
}

void runAddPage(WebPages *W, char* s) {
    if (isFullWeb(*W)) {
        printf("[ERROR] Database website sudah penuh! Tidak bisa menambah halaman baru.\n");
        return;
    }

    char content[10000];
    printf("Masukkan Konten (akhiri dengan '.' lalu Enter): ");
    int i = 0;
    char temp_char;
    int c;
    while ((c = getchar()) == '\n' || c == ' ' || c == '\r');
    if (c != EOF && c != '.') {
        content[i++] = c;
        while ((temp_char = getchar()) != '.' && temp_char != EOF && i < 9999) {
            content[i++] = temp_char;
        }
    }
    content[i] = '\0';
    while ((c = getchar()) != '\n' && c != EOF);

    int new_id = getMaxPageId(W) + 1;

    AddWeb(W, new_id, s, content);
    printf("[SUCCESS] Halaman %s berhasil ditambahkan!\n", s);
}

void runDeletePage(WebPages *W, Map *M, char* s, const char *pages_folder, const char *links_filepath) {
    if (isEmptyWeb(*W)) {
        printf("[ERROR] Database website kosong!\n");
        return;
    }

    int del_idx = -1;
    int target_id = -1;
    for (int i = 0; i < W->NEff; i++) {
        if (strcmp(W->buffer[i].web_url, s) == 0) {
            del_idx = i;
            target_id = W->buffer[i].id;
            break;
        }
    }

    if (del_idx == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", s);
    } else {
        deleteAdj(del_idx, W->NEff);
        
        RemoveWeb(W, target_id);
        
        unsetMap(s, M);
        
        SaveToCSV(*W, pages_folder);
        SaveLinkedPages(W, links_filepath);        
        printf("[SUCCESS] Halaman %s berhasil dihapus!\n", s);
    }
}

void runEditPage(WebPages *W, Map *M, char* s, const char *pages_folder) {
    if (isEmptyWeb(*W)) {
        printf("[ERROR] Database website kosong!\n");
        return;
    }

    int target_idx = -1;
    for (int i = 0; i < W->NEff; i++) {
        if (strcmp(W->buffer[i].web_url, s) == 0) {
            target_idx = i;
            break;
        }
    }

    if (target_idx == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", s);
        return;
    }

    char content[10000];
    printf("Masukkan Konten Baru (akhiri dengan '.' lalu Enter): ");
    
    int i = 0;
    char temp_char;
    int c;
    while ((c = getchar()) == '\n' || c == ' ' || c == '\r');
    if (c != EOF && c != '.') {
        content[i++] = c;
        while ((temp_char = getchar()) != '.' && temp_char != EOF && i < 9999) {
            content[i++] = temp_char;
        }
    }
    content[i] = '\0';
    while ((c = getchar()) != '\n' && c != EOF);

    strcpy(W->buffer[target_idx].content, content);

    setMap(s, content, M);
    
    SaveToCSV(*W, pages_folder);
    
    printf("[SUCCESS] Halaman %s berhasil diedit!\n", s);
}