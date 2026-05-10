// Include any necessary headers
#include <stdio.h>
#include "../header/master.h"

void printBanner() {
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("           ##                                                                   \n");
    printf("           ##                                                                   \n");
    printf("           ##                                                                   \n");
    printf("  :####    ##        ##.###:    ##.####    .####.                ####:    .####.  \n");
    printf("  ######   ##        #######:   #######   .######.              #######  .######. \n");
    printf("  #:   :## ##        ###  ###   ###.      ###  ###              ##:  :#  ###  ### \n");
    printf("   :#####  ##        ##.  .##   ##        ##.  .##             ##.       ##.  .## \n");
    printf(" .#######  ##        ##    ##   ##        ##    ##             ##        ##    ## \n");
    printf(" ## .  ##  ##        ##.  .##   ##        ##.  .##             ##.       ##.  .## \n");
    printf(" ##:  ###  ##        ###  ###   ##        ###  ###     ##      ##:  .#  ###  ### \n");
    printf(" ########  ########  #######:   ##        .######.     ##      #######  .######. \n");
    printf("   ###.##  ########  ##.###:    ##         .####.      ##       ####:    .####.  \n");
    printf("                     ##                                                         \n");
    printf("                     ##                                                         \n");
    printf("                     ##                                                         \n");
    printf("                                                                                \n");
}

int main() {
    WebPages W;
    Map M;
    LoadFromCSV(&W, "data.csv");
    CreateMap(&M);
    printBanner();
    
    while(true){
        printf("\nSelamat datang di website hitam-putih, silakan gunakan fasilitas seadanya\n");
        printf("[1] open\n");
        printf(">>");
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "open") == 0) {
            char url[100];
            scanf("%s", url);

            openpage(url, &W, &M);
        }
    }
    
    return 0;
}