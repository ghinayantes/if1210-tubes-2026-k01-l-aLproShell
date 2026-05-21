#include "../../header/pagemanagement.h"

void runAddPage(WebPages *W) {
    if (isFullWeb(*W)) {
        printf("[ERROR] Database website sudah penuh! Tidak bisa menambah halaman baru.\n");
        return;
    }

    char url[100];
    char content[1000];

    printf("Masukkan URL: ");
    scanf("%s", url);

    if (!isUniqueWeb(*W, url)) {
        printf("[ERROR] URL %s sudah ada di database!\n", url);
        return;
    }

    printf("Masukkan Konten: ");
    scanf(" %[^\n]", content);

    int new_id = 1;
    if (!isEmptyWeb(*W)) {
        new_id = W->buffer[W->NEff - 1].id + 1;
    }

    AddWeb(W, new_id, url, content);
    printf("[SUCCESS] Halaman %s berhasil ditambahkan!\n", url);
}

void runDeletePage(WebPages *W) {
    if (isEmptyWeb(*W)) {
        printf("[ERROR] Database website kosong!\n");
        return;
    }

    char url[100];
    printf("Masukkan URL yang ingin dihapus: ");
    scanf("%s", url);

    int target_id = -1;
    for (int i = 0; i < W->NEff; i++) {
        if (strcmp(W->buffer[i].web_url, url) == 0) {
            target_id = W->buffer[i].id;
            break;
        }
    }

    if (target_id == -1) {
        printf("[ERROR] URL %s tidak ditemukan di database!\n", url);
    } else {

        RemoveWeb(W, target_id);
        printf("[SUCCESS] Halaman %s berhasil dihapus!\n", url);
    }
}