#include "../header/saveload.h"
#include <stdio.h>

void exitProgram() {
    char pilih;
    char folder[100];
    
    printf("Save data before exiting? (y/n)\n");
    scanf(" %c", &pilih);

    if (pilih == 'y' || pilih == 'Y') {

        printf("Please input the save folder\n");
        scanf("%s", folder);

        SavetoCSV(folder);
    }

    printf("Goodbye~\n");
}
