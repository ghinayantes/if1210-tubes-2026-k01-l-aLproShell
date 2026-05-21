#include "../../header/pagemanagement.h"

void runAddPage(WebPages *W, char* s) {
    if (isFullWeb(*W)) {
        printf("[ERROR] Database website sudah penuh! Tidak bisa menambah halaman baru.\n");
        return;
    }

    char content[10000];

    printf("Masukkan Konten: ");
    scanf(" %[^\n]", content);

    int new_id = 1;
    if (!isEmptyWeb(*W)) {
        new_id = W->buffer[W->NEff - 1].id + 1;
    }

    AddWeb(W, new_id, s, content);
    printf("[SUCCESS] Halaman %s berhasil ditambahkan!\n", s);
}

void runDeletePage(WebPages *W, char* s) {
    if (isEmptyWeb(*W)) {
        printf("[ERROR] Database website kosong!\n");
        return;
    }


    int target_id = -1;
    for (int i = 0; i < W->NEff; i++) {
        if (strcmp(W->buffer[i].web_url, s) == 0) {
            target_id = W->buffer[i].id;
            break;
        }
    }

    if (target_id == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", s);
    } else {

        RemoveWeb(W, target_id);
        printf("[SUCCESS] Halaman %s berhasil dihapus!\n", s);
    }
}