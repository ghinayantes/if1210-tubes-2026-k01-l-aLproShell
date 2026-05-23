#include "exit.h"
#include <stdio.h>

void exitProgram(WebPages W) {
    char pilih;
    char folder[100];
    
    printf("Save data before exiting? (y/n)\n");
    scanf(" %c", &pilih);

    if (pilih == 'y' || pilih == 'Y') {

        printf("Please input the save folder\n");
        scanf("%s", folder);

        SavetoCSV(W, folder);
    }

    printf("Goodbye~\n");
}
