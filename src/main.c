<<<<<<< HEAD
// Include any necessary headers
#include <stdio.h>
#include "master.h"

// Fungsi helper untuk membersihkan sisa input di buffer
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printBanner() {
    printf("\033[1;36m");
    printf("   █████████   ████                                █████████  █████               ████  ████ \n");
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
    printf("\033[0m");
}

void printMenu() {
    printf("\n");
    printf("\033[1;36m  ██ AlproShell Commands \033[0m\n");
    printf("\033[0;90m  ┌────────────────────────────┬─────────────────────────────┐\033[0m\n");
    printf("  │  [1]  discover             │  [10] viewhistory           │\n");
    printf("  │  [2]  open <url>           │  [11] back                  │\n");
    printf("  │  [3]  search <str>         │  [12] forward               │\n");
    printf("  │  [4]  newtab               │  [13] add_page              │\n");
    printf("  │  [5]  checktab             │  [14] delete_page           │\n");
    printf("  │  [6]  prevtab <x>          │  [15] edit_page             │\n");
    printf("  │  [7]  nexttab <x>          │  [16] load <dir/>           │\n");
    printf("  │  [8]  closetab             │  [17] save <dir/>           │\n");
    printf("  │  [9]  download <url>       │  [18] exit                  │\n");
    printf("\033[0;90m  └────────────────────────────┴─────────────────────────────┘\033[0m\n");
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
    loadData(&W);

    printBanner();
    printf("\nSelamat datang di AlproShell! Berikut adalah beberapa command yang bisa digunakan.\nGunakan \033[1mhelp\033[0m jika ingin melihat kembali command yang tersedia.\n");
    printMenu();

    while(true){
        printf("\n>> ");
        char command[100];
        scanf(" %s", command);  // spasi di depan untuk skip newline sisa

        if (strcmp(command, "discover") == 0) {
            flushInput();
            runDiscover(&W, &discover_seed);
        }

        else if (strcmp(command, "open") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            printf("\n");
            if(isWebsiteValid(url)) {
                printf("\033[1;36m  ██ Available Commands \033[0m\n");
                printf("  Jika ingin mengakses linked pages yang tersedia, gunakan \033[1mopenlinked <x>\033[0m\n");
                printf("\n");
                openpage(url, &W, &M, &TL);
            }
            else printf("Format domain tidak valid, tolong tulis domain kembali.");
        }

        else if (strcmp(command, "search") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();
            printf("Search result(s) for %s :\n", url);
            boyerMoore(url, W);
        }

        else if (strcmp(command, "newtab") == 0) {
            flushInput();
            newTab(&TL);
        }

        else if (strcmp(command, "checktab") == 0) {
            flushInput();
            checkTab(&TL);
        }

        else if (strcmp(command, "prevtab") == 0) {
            scanf(" %d", &tab);
            flushInput();
            prevTab(&TL, tab);
        }

        else if (strcmp(command, "nexttab") == 0) {
            scanf(" %d", &tab);
            flushInput();
            nextTab(&TL, tab);
        }

        else if (strcmp(command, "closetab") == 0) {
            flushInput();
            closeTab(&TL);
        }

        else if (strcmp(command, "download") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();
            if(isWebsiteValid(url)) {
                printf("\n\033[1;36m  ██ Available Commands \033[0m\n");
                printf("  Untuk menambah progress download suatu website, gunakan \033[1mtick\033[0m\n\n");
                DownloadQueueDownload(&DQ, url);
            }
        }

        else if (strcmp(command, "tick") == 0) {
            flushInput();
            DownloadTick(&DQ);
        }

        else if (strcmp(command, "viewhistory") == 0) {
            flushInput();
            int aktif = TL.currentIdx;
            viewTabHistory(&(TL.tabs[aktif].tabHistory));
        }

        else if (strcmp(command, "back") == 0) {
            int langkah;
            scanf(" %d", &langkah);
            flushInput();
            int aktif = TL.currentIdx;
            back(&(TL.tabs[aktif].tabHistory), langkah);

            if (!TL.tabs[aktif].tabHistory.Empty) {
                char *urlSekarang = TL.tabs[aktif].tabHistory.currentTab.url;
                char *isiHalaman = getMap(urlSekarang, &M);
                if (isiHalaman != NULL) {
                    printReal(isiHalaman); 
                    printf("\n");
                } else {
                    isiHalaman = getWeb(urlSekarang, &W);
                    if (isiHalaman != NULL) {
                        printReal(isiHalaman);
                        printf("\n");
                    }
                }
            }
        }

        else if (strcmp(command, "forward") == 0) {
            int langkah;
            scanf(" %d", &langkah);
            flushInput();
            int aktif = TL.currentIdx;
            forward(&(TL.tabs[aktif].tabHistory), langkah);
            
            if (!TL.tabs[aktif].tabHistory.Empty) {
                char *urlSekarang = TL.tabs[aktif].tabHistory.currentTab.url;
                char *isiHalaman = getMap(urlSekarang, &M);
                if (isiHalaman != NULL) {
                    printReal(isiHalaman); 
                    printf("\n");
                } else {
                    isiHalaman = getWeb(urlSekarang, &W);
                    if (isiHalaman != NULL) {
                        printReal(isiHalaman);
                        printf("\n");
                    }
                }
            }
        }

        else if (strcmp(command, "add_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)){
                if(!isUniqueWeb(W, url)){
                    printf("[ERROR] URL %s sudah ada di database!\n", url);
                }
                else{
                    runAddPage(&W, url);
                }
            } 
            else printf("Format domain tidak valid, tolong tulis domain kembali.");   
        }

        else if (strcmp(command, "delete_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)) runDeletePage(&W, &M, url);
            else printf("Format domain tidak valid, tolong tulis domain kembali.");
        }

        else if (strcmp(command, "edit_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)) {
                runEditPage(&W, &M, url);
            } 
            else {
                printf("Format domain tidak valid, tolong tulis domain kembali."); 
            }  
        }

        else if (strcmp(command, "load") == 0) {
            char path[256];
            scanf(" %s", path);
            flushInput();

            char database[512];
            loadAgain(path, database);

            if(LoadFromCSV(&W, database)){
                DestroyMap(&M);
                CreateMap(&M);
                printf("%d Website dari database telah di-load ulang...\n\n", W.NEff); 
                printBanner();
                printf("\nSelamat datang di AlproShell! Berikut adalah beberapa command yang bisa digunakan.\nGunakan \033[1mhelp\033[0m jika ingin melihat kembali command yang tersedia.\n");
                printMenu();           
            } 
            else{
                printf("Gagal me-load website dari %s\n", database);
            }
        }

        else if (strcmp(command, "save") == 0) {
            char path[256];
            scanf(" %s", path);
            flushInput();

            int len = strlen(path);
            if (len > 0 && path[len - 1] != '/') {
                strcat(path, "/");
            }

            if(SaveToCSV(W, path)){}
        }

        else if (strcmp(command, "help") == 0) {
            flushInput();
            printMenu();
        }

        else if (strcmp(command, "exit") == 0) {
            printf("Sampai jumpa!\n");
            return 0;
        }

        else {
            flushInput();
            printf("Command tidak dikenal: %s\n", command);
        }
    }
    
    return 0;
}
=======
// Include any necessary headers
#include <stdio.h>
#include "master.h"

// Fungsi helper untuk membersihkan sisa input di buffer
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printBanner() {
    printf("\033[1;36m");
    printf("   █████████   ████                                █████████  █████               ████  ████ \n");
    printf("  ███░░░░░███ ░░███                               ███░░░░░███░░███               ░░███ ░░███ \n");
    printf(" ░███    ░███  ░███  ████████  ████████   ██████ ░███     ░░░  ░███████    ██████  ░███  ░███ \n");
    printf(" ░███████████  ░███ ░░███░░███░░███░░███ ███░░███░░█████████  ░███░░███  ███░░███ ░███  ░███ \n");
    printf(" ░███░░░░░███  ░███  ░███ ░███ ░███ ░░░ ░███ ░███ ░░░░░░░░███ ░███ ░███ ░███████  ░███  ░███ \n");
    printf(" ░███    ░███  ░███  ░███ ░███ ░███     ░███ ░███ ███    ░███ ░███ ░███ ░███░░░   ░███  ░███ \n");
    printf(" █████   █████ █████ ░███████  █████    ░░██████ ░░█████████  ████ █████░░██████  █████ █████\n");
    printf("░░░░░   ░░░░░ ░░░░░  ░███░░░  ░░░░░      ░░░░░░   ░░░░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░ \n");
    printf("                     ░███                                                                    \n");
    printf("                     █████                                                                   \n");
    printf("                    ░░░░░                                                                    \n");
    printf("\033[0m");
}

void printMenu() {
    printf("\n");
    printf("\033[1;36m  ██ AlproShell Commands \033[0m\n");
    printf("\033[0;90m  ┌────────────────────────────┬─────────────────────────────┐\033[0m\n");
    printf("  │  [1]  discover             │  [10] viewhistory           │\n");
    printf("  │  [2]  open <url>           │  [11] back                  │\n");
    printf("  │  [3]  search <str>         │  [12] forward               │\n");
    printf("  │  [4]  newtab               │  [13] add_page              │\n");
    printf("  │  [5]  checktab             │  [14] delete_page           │\n");
    printf("  │  [6]  prevtab <x>          │  [15] edit_page             │\n");
    printf("  │  [7]  nexttab <x>          │  [16] load <dir/>           │\n");
    printf("  │  [8]  closetab             │  [17] save <dir/>           │\n");
    printf("  │  [9]  download <url>       │  [18] exit                  │\n");
    printf("  │  [9]  download <url>       │  [18] exit                  │\n");
    printf("\033[0;90m  └────────────────────────────┴─────────────────────────────┘\033[0m\n");
}

int main() {
    int tab;
    unsigned int discover_seed = 12345;
    WebPages *W = (WebPages *)malloc(sizeof(WebPages));
    Map *M      = (Map *)malloc(sizeof(Map));
    TabsList *TL = (TabsList *)malloc(sizeof(TabsList));
    
    // Check if malloc succeeded
    if (W == NULL || M == NULL || TL == NULL) {
        printf("Gagal alokasi memori di heap!\n");
        return 1;
    }
    DownloadQueue DQ;
    CreateWeb(W);
    CreateMap(M);
    tabsListInit(TL);
    DownloadQueueInit(&DQ);
    loadData(W);
    LoadLinkedPages(W, "config/linked_pages.csv");

    // TO SEE IF THE DATABASE ACTUALLY LOADED
    // if(loadData(W)) printf("\n%d Website dari database telah di-load otomatis...\n", W.NEff);

    printBanner();
    printf("\nSelamat datang di AlproShell! Berikut adalah beberapa command yang bisa digunakan.\nGunakan \033[1mhelp\033[0m jika ingin melihat kembali command yang tersedia.\n");
    printMenu();

    while(true){
        printf("\n>> ");
        char command[100];
        scanf(" %s", command);
        if (strcmp(command, "discover") == 0) {
            flushInput();
            runDiscover(W, &discover_seed);
        }

        else if (strcmp(command, "open") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            printf("\n");
            if(isWebsiteValid(url)) {
                printf("\033[1;36m  ██ Available Commands \033[0m\n");
                printf("  Jika ingin mengakses linked pages yang tersedia, gunakan \033[1mopenlinked <x>\033[0m\n");
                printf("\n");
                cmd_open(url, W, M, TL);
            }
            else printf("Format domain tidak valid, tolong tulis domain kembali.");
        }

        else if (strcmp(command, "openlinked") == 0) {
            int x;
            scanf("%d", &x);
            openLinked(x, W, M, TL);
        }

        else if (strcmp(command, "search") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();
            printf("Search result(s) for %s :\n", url);
            boyerMoore(url, *W);
        }

        else if (strcmp(command, "newtab") == 0) {
            flushInput();
            newTab(TL);
        }

        else if (strcmp(command, "checktab") == 0) {
            flushInput();
            checkTab(TL);
        }

        else if (strcmp(command, "prevtab") == 0) {
            scanf(" %d", &tab);
            flushInput();
            prevTab(TL, tab);
        }

        else if (strcmp(command, "nexttab") == 0) {
            scanf(" %d", &tab);
            flushInput();
            nextTab(TL, tab);
        }

        else if (strcmp(command, "closetab") == 0) {
            flushInput();
            closeTab(TL);
        }

        else if (strcmp(command, "download") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();
            if(isWebsiteValid(url)) {
                printf("\n\033[1;36m  ██ Available Commands \033[0m\n");
                printf("  Untuk menambah progress download suatu website, gunakan \033[1mtick\033[0m\n\n");
                DownloadQueueDownload(&DQ, url);
            }
        }

        else if (strcmp(command, "tick") == 0) {
            flushInput();
            DownloadTick(&DQ);
        }

        else if (strcmp(command, "viewhistory") == 0) {
            flushInput();
            int aktif = TL->currentIdx;
            viewTabHistory(&(TL->tabs[aktif].tabHistory));
        }

        else if (strcmp(command, "back") == 0) {
            int langkah;
            scanf(" %d", &langkah);
            flushInput();
            int aktif = TL->currentIdx;
            back(&(TL->tabs[aktif].tabHistory), langkah);

            if (!TL->tabs[aktif].tabHistory.Empty) {
                char *urlSekarang = TL->tabs[aktif].tabHistory.currentTab.url;
                char *isiHalaman = getMap(urlSekarang, M);
                if (isiHalaman != NULL) {
                    printReal(isiHalaman); 
                    printf("\n");
                } else {
                    isiHalaman = getWeb(urlSekarang, W);
                    if (isiHalaman != NULL) {
                        printReal(isiHalaman);
                        printf("\n");
                    }
                }
            }
        }

        else if (strcmp(command, "forward") == 0) {
            int langkah;
            scanf(" %d", &langkah);
            flushInput();
            int aktif = TL->currentIdx;
            forward(&(TL->tabs[aktif].tabHistory), langkah);
            
            if (!TL->tabs[aktif].tabHistory.Empty) {
                char *urlSekarang = TL->tabs[aktif].tabHistory.currentTab.url;
                char *isiHalaman = getMap(urlSekarang, M);
                if (isiHalaman != NULL) {
                    printReal(isiHalaman); 
                    printf("\n");
                } else {
                    isiHalaman = getWeb(urlSekarang, W);
                    if (isiHalaman != NULL) {
                        printReal(isiHalaman);
                        printf("\n");
                    }
                }
            }
        }

        else if (strcmp(command, "add_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)){
                if(!isUniqueWeb(*W, url)){
                    printf("[ERROR] URL %s sudah ada di database!\n", url);
                }
                else{
                    runAddPage(W, url);
                }
            } 
            else printf("Format domain tidak valid, tolong tulis domain kembali.");   
        }

        else if (strcmp(command, "delete_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)) runDeletePage(W, url);
            else printf("Format domain tidak valid, tolong tulis domain kembali.");
        }

        else if (strcmp(command, "edit_page") == 0) {
            char url[100];
            scanf(" %s", url);
            flushInput();

            if(isWebsiteValid(url)) {
                runEditPage(W, url);
            } 
            else {
                printf("Format domain tidak valid, tolong tulis domain kembali."); 
            }  
        }

        else if (strcmp(command, "load") == 0) {
            char path[256];
            scanf(" %s", path);
            flushInput();

            char database[512];
            loadAgain(path, database);

            if(LoadFromCSV(W, database)){
                DestroyMap(M);
                CreateMap(M);
                printf("%d Website dari database telah di-load ulang...\n\n", W->NEff); 
                printBanner();
                printf("\nSelamat datang di AlproShell! Berikut adalah beberapa command yang bisa digunakan.\nGunakan \033[1mhelp\033[0m jika ingin melihat kembali command yang tersedia.\n");
                printMenu();           
            } 
            else{
                printf("Gagal me-load website dari %s\n", database);
            }
        }

        else if (strcmp(command, "save") == 0) {
            char path[256];
            scanf(" %s", path);
            flushInput();

            int len = strlen(path);
            if (len > 0 && path[len - 1] != '/') {
                strcat(path, "/");
            }

            if(SaveToCSV(*W, path)){}
        }

        else if (strcmp(command, "help") == 0) {
            flushInput();
            printMenu();
        }

        else if (strcmp(command, "exit") == 0) {
            char path[256] = "";
            exitProgram(W, path);
            free(TL);
            free(W);
            free(M);
            return 0;
        }
    }
    
    return 0;
}
>>>>>>> 71bcd6bc3412778d98138ae67cfeccc0aeb7b158
