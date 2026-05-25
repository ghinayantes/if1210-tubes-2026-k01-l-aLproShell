#include "exit.h"
#include <stdio.h>

void exitProgram(WebPages *W, char *f) {
    char pilih;    
    printf("Save data before exiting? (y/n)\n");
    scanf(" %c", &pilih);

    if (pilih == 'y' || pilih == 'Y') {
        printf("Please input the save folder\n");
        scanf("%s", f);

        int len = strlen(f);
        if (len>0 && f[len-1] != '/') {
            strcat(f,"/");
        }
        if (SaveToCSV(*W, f)) {
            printf("Data berhasil disimpan di %s!\n", f);
        } else {
            printf("Data gagal disimpan!!!\n");
        }
    }
    printf("Selamat tinggal!\n");
}
