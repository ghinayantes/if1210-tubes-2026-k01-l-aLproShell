#include "exit.h"
#include <stdio.h>

void exitProgram(WebPages *W, TabsList *TL, GlobalHistory *PQ, char *f) {
    char pilih;    
    printf("Apakah mau menyimpan data sebelum keluar program? (y/n)\n");
    scanf(" %c", &pilih);

    if (pilih == 'y' || pilih == 'Y') {
        printf("Tolong masukkan save folder\n");
        scanf("%s", f);

        int len = strlen(f);
        if (len>0 && f[len-1] != '/') {
            strcat(f,"/");
        }
        if (SaveToCSV(*W, f)) {
            if (!SaveConfig(TL, PQ, f)) {
                printf("PERINGATAN: config.txt tidak tersimpan.\n");
            }

            char linkedPath[512];
            strcpy(linkedPath, f);
            strcat(linkedPath, "linked_pages.csv");

            if (!SaveLinkedPages(W, linkedPath)) {
                printf("PERINGATAN: linked_pages.csv tidak tersimpan.\n");
            }

            printf("Data berhasil disimpan di %s!\n", f);
        } else {
            printf("Data gagal disimpan!!!\n");
        }
    }
    printf("Selamat tinggal!\n");
}
