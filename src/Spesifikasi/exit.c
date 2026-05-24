#include "exit.h"
#include <stdio.h>

void exitProgram(WebPages *W, char *f) {
    char pilih;    
    printf("Save data before exiting? (y/n)\n");
    scanf(" %c", &pilih);

    if (pilih == 'y' || pilih == 'Y') {

        printf("Please input the save folder\n");
        scanf("%s", f);

        SaveToCSV(*W, f);
    }

    printf("Selamat tinggal!\n");
}
