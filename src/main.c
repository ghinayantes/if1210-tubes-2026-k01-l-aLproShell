// Include any necessary headers
#include <stdio.h>
#include "master.h"

static void loadAgain(const char *path, char *out) {
    char temp[1024]; 
    memset(temp, 0, sizeof(temp));

    if (path == NULL || strlen(path) == 0) {
        strcpy(out, "config/data.csv");
        return;
    }    
    strcpy(temp, path);
    int len = strlen(temp);

    while (len > 0 && temp[len - 1] == '/') {
        temp[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        strcpy(out, "config/data.csv");
        return;
    }

    if (len >= 4 && temp[len - 4] == '.' && temp[len - 3] == 'c' && temp[len - 2] == 's' && temp[len - 1] == 'v') {
        strcpy(out, temp);
        return;
    }

    strcpy(out, temp);
    strcat(out, "/data.csv");
}

static boolean loadData(WebPages *W) {
    if (LoadFromCSV(W, "config/data.csv")) return true;
    return false;
}

void printBanner() {
    printf("█████████   ████                                █████████  █████               ████  ████ \n");
    printf("  ███░░░░░███ ░░███                               ███░░░░░███░░███               ░░███ ░░███ \n");
    printf(" ░███    ░███  ░███  ████████  ████████   ██████ ░███    ░░░  ░███████    ██████  ░███  ░███ \n");
    printf(" ░███████████  ░███ ░░███░░███░░███░░███ ███░░███░░█████████  ░███░░███  ███░░███ ░███  ░███ \n");
    printf(" ░███░░░░░███  ░███  ░███ ░███ ░███ ░░░ ░███ ░███ ░░░░░░░░███ ░███ ░███ ░███████  ░███  ░███ \n");
    printf(" ░███    ░███  ░███  ░███ ░███ ░███     ░███ ░███ ███    ░███ ░███ ░███ ░███░░░   ░███  ░███ \n");
    printf(" █████   █████ █████ ░███████  █████    ░░██████ ░░█████████  ████ █████░░██████  █████ █████\n");
    printf("░░░░░   ░░░░░ ░░░░░  ░███░░░  ░░░░░      ░░░░░░   ░░░░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░ \n");
    printf("                     ░███                                                                    \n");
    printf("                     █████                                                                   \n");
    printf("                    ░░░░░                                                                    \n");
}

int main() {
    int tab;
    WebPages W;
    Map M;
    unsigned int discover_seed = 12345;
    TabsList TL;
    DownloadQueue DQ;
    CreateWeb(&W);
    CreateMap(&M);
    tabsListInit(&TL);
    DownloadQueueInit(&DQ);
    
    printBanner();

    if(loadData(&W)){
        printf("\n%d Website dari database telah di-load otomatis...\n", W.NEff);
    }

    while(true){
        printf("\nSelamat datang di website Nagor Falls, silakan gunakan semua alat dibawah ini sebelum Anda mengidap penyakit nangor gila\n");
        printf("[1] open\n");
        printf("[2] search\n");
        printf("[3] newtab\n");
        printf("[4] checktab\n");
        printf("[5] prevtab\n");
        printf("[6] nexttab\n");
        printf("[7] closetab\n");
        printf("[8] download\n");
        printf("[9] discover\n");
        printf("[10] addpage\n");
        printf("[11] deletepage\n");

        printf("\n>>");
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "open") == 0) {
            char url[100];
            scanf("%s", url);

            openpage(url, &W, &M);
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

        else if (strcmp(command, "closetab") == 0) {
            closeTab(&TL);
        }

        else if (strcmp(command, "download") == 0) {
            char url[100];
            scanf("%s", url);
            DownloadQueueDownload(&DQ, url);
        }

        else if (strcmp(command, "tick") == 0) {
            DownloadTick(&DQ);
        }

        else if (strcmp(command, "discover") == 0) {
            runDiscover(&W, &discover_seed);
        }

        else if (strcmp(command, "addpage") == 0) {
            runAddPage(&W);
        }

        else if (strcmp(command, "deletepage") == 0) {
            runDeletePage(&W);
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