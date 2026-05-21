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
        printf("[2] search\n");
        printf("[3] newtab\n");
        printf("[4] checktab\n");
        printf("[5] prevtab\n");
        printf("[6] nexttab\n");
        printf("[7] closetab\n");
        printf("[8] download\n");
        printf("[9] viewhistory\n");
        printf("[10] back\n");
        printf("[11] forward\n");

        printf("\n>>");
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "open") == 0) {
            char url[100];
            scanf("%s", url);

            openpage(url, &W, &M);
            openpage(url, &W, &M, &TL);
        }

        else if (strcmp(command, "search") == 0) {
            char url[100];
            scanf("%s", url);

            boyerMoore(url, W);
        }

        else if (strcmp(command, "checktab") == 0) {
            checkTab(&TL);
        }

        else if (strcmp(command, "newtab") == 0) {
            newTab(&TL);
        }

        else if (strcmp(command, "closetab") == 0) {
            closeTab(&TL);
        }

        else if (strcmp(command, "nexttab") == 0) {
            scanf("%d", &tab);

            nextTab(&TL, tab);
        }

        else if (strcmp(command, "prevtab") == 0) {
            
            scanf("%d", &tab);

            prevTab(&TL, tab);
        }

        else if (strcmp(command, "download") == 0) {
            char url[100];
            scanf("%s", url);
            DownloadQueueDownload(&DQ, url);
        }

        else if (strcmp(command, "back") == 0) {
            int langkah;
            scanf("%d", &langkah);
            int aktif = TL.currentIdx;
            back(&(TL.tabs[aktif].tabHistory), langkah);
        }

        else if (strcmp(command, "forward") == 0) {
            int langkah;
            scanf("%d", &langkah);
            int aktif = TL.currentIdx;
            forward(&(TL.tabs[aktif].tabHistory), langkah);
        }

        else if (strcmp(command, "viewhistory") == 0) {
            int aktif = TL.currentIdx;
            viewTabHistory(&(TL.tabs[aktif].tabHistory));
        }

        else if (strcmp(command, "tick") == 0) {
            DownloadTick(&DQ);
        }

        else if (strcmp(command, "load") == 0) {
            char path[256];
            scanf("%s", path);

            char database[512];
            loadAgain(path, database);

            if(LoadFromCSV(&W, database)){
                DestroyMap(&M);
                CreateMap(&M);
                printf("%d Website dari database telah di-load ulang...\n", W.NEff);            
            } 
            else{
                printf("Gagal me-load website dari %s\n", database);
            }
        }
    }
    
    return 0;
}