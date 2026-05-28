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
    if (W->NEff >= 100) {
        printf("[ERROR] Database website sudah penuh!\n");
        return;
    }

    char content[10000] = "";
    char line[512];
    printf("Masukkan konten (Akhiri dengan titik '.' di baris baru):\n");
    
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strcmp(line, ".") == 0) {
            break;
        }
        if (strlen(content) + strlen(line) + 2 < 10000) {
            strcat(content, line);
            strcat(content, "\n");
        }
    }

    int new_id = getMaxPageId(W) + 1;
    int new_idx = W->NEff;
    
    W->buffer[new_idx].id = new_id;
    strcpy(W->buffer[new_idx].web_url, s);
    strcpy(W->buffer[new_idx].content, content);
    W->NEff++;

    for (int i = 0; i < 100; i++) {
        adj[new_idx][i] = 0;
        adj[i][new_idx] = 0;
    }

    printf("Masukkan linked pages (Ketik 'DONE' jika sudah selesai):\n");
    char link_url[256];
    while (1) {
        printf(">>> ");
        if (!fgets(link_url, sizeof(link_url), stdin)) break;
        link_url[strcspn(link_url, "\r\n")] = 0;

        if (strcmp(link_url, "DONE") == 0) {
            break;
        }

        int target_idx = findUrl(W, link_url);

        if (target_idx == -1) {
            printf("URL tidak ditemukan!\n");
        } else {
            adj[new_idx][target_idx] = 1; 
            printf("Berhasil menghubungkan ke %s\n", link_url);
        }
    }

    SaveToCSV(*W, "config/");
    SaveLinkedPages(W, "config/linked_pages.csv");
    printf("Halaman %s berhasil ditambahkan!\n", s);
}

void runDeletePage(WebPages *W, Map *M, char* s, const char *pages_folder, const char *links_filepath) {
    int del_idx = findUrl(W, s);

    if (del_idx == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", s);
        return;
    }

    unsetMap(s, M);
    printf("[Status: Cache-Hit] URL ditemukan di cache dan telah dibersihkan\n");

    deleteAdj(del_idx, W->NEff);

    for (int i = del_idx; i < W->NEff - 1; i++) {
        W->buffer[i] = W->buffer[i + 1];
    }
    W->NEff--;

    SaveToCSV(*W, pages_folder);
    SaveLinkedPages(W, links_filepath);        
    printf("Halaman %s berhasil dihapus!\n", s);
}

void runEditPage(WebPages *W, Map *M, char* s, const char *pages_folder) {
    int target_idx = findUrl(W, s);

    if (target_idx == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", s);
        return;
    }

    unsetMap(s, M);

    printf("Konten saat ini:\n%s\n", W->buffer[target_idx].content);
    printf("Linked pages saat ini:\n");
    displayLinkedPages(W, target_idx);
    printf("\n");

    char new_content[10000] = "";
    char line[512];
    printf("Masukkan konten baru (akhiri dengan '.' atau ketik '.' saja jika tidak ingin diubah):\n");
    
    int is_first_line = 1;
    int update_content = 1;
    
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (is_first_line && strcmp(line, ".") == 0) {
            update_content = 0;
            break;
        }
        is_first_line = 0;
        if (strcmp(line, ".") == 0) {
            break;
        }
        if (strlen(new_content) + strlen(line) + 2 < 10000) {
            strcat(new_content, line);
            strcat(new_content, "\n");
        }
    }

    if (update_content) {
        strcpy(W->buffer[target_idx].content, new_content);
    }

    printf("Masukkan linked pages baru (Ketik 'DONE' untuk selesai, atau 'SKIP' jika tidak ingin mengubah link):\n");
    char edit_link[256];
    int cleared_old_links = 0;

    while (1) {
        printf(">>> ");
        if (!fgets(edit_link, sizeof(edit_link), stdin)) break;
        edit_link[strcspn(edit_link, "\r\n")] = 0;

        if (strcmp(edit_link, "SKIP") == 0) {
            break; 
        }
        if (strcmp(edit_link, "DONE") == 0) {
            break;
        }

        if (!cleared_old_links) {
            for (int i = 0; i < 100; i++) {
                adj[target_idx][i] = 0;
            }
            cleared_old_links = 1;
        }

        int link_target_idx = findUrl(W, edit_link);

        if (link_target_idx == -1) {
            printf("URL tidak ditemukan!\n");
        } else {
            adj[target_idx][link_target_idx] = 1;
            printf("Berhasil menghubungkan ke %s\n", edit_link);
        }
    }

    SaveToCSV(*W, pages_folder);
    char linkedPath[512];
    strcpy(linkedPath, pages_folder);
    strcat(linkedPath, "linked_pages.csv");
    SaveLinkedPages(W, linkedPath);
    
    printf("Halaman %s berhasil diperbarui!\n", s);
}