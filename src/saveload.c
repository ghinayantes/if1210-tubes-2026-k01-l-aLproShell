#include "saveload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tabParser(const char *s){
    if(s == NULL) return 0;
    if(s[0] != 'T' || s[1] != 'A' || s[2] != 'B') return 0;
    
    const char *p = s + 3;
    if(*p == '\0') return 0;
    
    int v = atoi(p);
    return v;
}

void setWebname(Webname *w, const char *url) {
    if(w == NULL) return;
    
    if(url == NULL){
        w->url[0] = '\0';
        return;
    }
    
    int maxSize = sizeof(w->url) - 1;
    int i = 0;
    
    while(url[i] != '\0' && i < maxSize){
        w->url[i] = url[i];
        i++;
    }
    
    w->url[i] = '\0';
}


boolean LoadFromCSV(WebPages *W, const char *path) {
    FILE *file = fopen(path, "r");
    if(!file){
        return false;
    } 

    W->NEff = 0;
    char line[20000];
    
    while(fgets(line, sizeof(line), file)){
        const char *p = line;
        int id;
        char url[100];
        char content[10000];

        char *end;
        id = (int)strtol(p, &end, 10);
        if(end == p) continue;

        p = end;

        char *data[2] = {url, content};
        int size[2] = {sizeof(url), sizeof(content)};
        boolean valid = true;

        for (int f = 0; f < 2 && valid; f++) 
        {
            if(*p != ',' || *(p+1) != '"'){ 
                valid = false; 
            }
            p += 2;

            int i = 0;
            boolean done = false;
            while(*p && !done){
                if(*p == '"'){
                    if(*(p+1) == '"'){        
                        if (i < size[f] - 1) data[f][i++] = '"';
                        p += 2;
                    } 
                    else{     
                        p++;
                        done = true;
                    }
                }
                else{
                    if(i < size[f] - 1){
                        data[f][i++] = *p;
                    } 
                    p++;
                }
            }
            data[f][i] = '\0';
        }

        if(valid) AddWeb(W, id, url, content);
    }

    fclose(file);
    return true;
}

boolean SaveToCSV(WebPages W, const char *folder) {
    char path[512];
    strcpy(path, folder);
    strcat(path, "web_pages.csv");

    FILE *check = fopen(path, "r");
    if(check){
        fclose(check);
        printf("WARNING: %s already exists, overwrite? (y/n): ", path);
        char ans;
        scanf(" %c", &ans);
        if (ans != 'y' && ans != 'Y') {
            printf("Save cancelled.\n");
            return false;
        }
        printf("Overwriting %s...\n", path);
    } 
    else{
        printf("Saving data into %s...\n", path);
    }

    FILE *file = fopen(path, "w");
    if(!file){
        printf("ERROR: Could not open %s for writing.\n", path);
        return false;
    }

    for(int i = 0; i < W.NEff; i++){
        fprintf(file, "%d,\"%s\",\"%s\"\n", W.buffer[i].id, W.buffer[i].web_url, W.buffer[i].content);
    }

    fclose(file);
    printf("Data saved!\n");
    return true;
}

void loadAgain(const char *path, char *out) {
    char temp[1024]; 
    memset(temp, 0, sizeof(temp));

    if (path == NULL || strlen(path) == 0) {
        strcpy(out, "config/web_pages.csv");
        return;
    }    
    strcpy(temp, path);
    int len = strlen(temp);

    while (len > 0 && temp[len - 1] == '/') {
        temp[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        strcpy(out, "config/web_pages.csv");
        return;
    }

    if (len >= 4 && temp[len - 4] == '.' && temp[len - 3] == 'c' && temp[len - 2] == 's' && temp[len - 1] == 'v') {
        strcpy(out, temp);
        return;
    }

    strcpy(out, temp);
    strcat(out, "/web_pages.csv");
}

boolean loadData(WebPages *W) {
    if (LoadFromCSV(W, "config/web_pages.csv")) return true;
    return false;
}

boolean LoadConfig(TabsList *TL, GlobalHistory *PQ, const char *f) {
    if(TL == NULL) return false;
    if(PQ != NULL) CreateGlobalHistory(PQ);

    FILE *file = fopen(f, "r");
    if(!file) return false;

    int cacheMax = 0;
    int tabsMax = 0;
    int downloadMax = 0;
    int maxPages = 0;
    int tabCount = 0;
    int activeIdx = 0;

    if(fscanf(file, "%d %d %d %d", &cacheMax, &tabsMax, &downloadMax, &maxPages) != 4){
        fclose(file);
        return false;
    }

    if(fscanf(file, "%d %d", &tabCount, &activeIdx) != 2){
        fclose(file);
        return false;
    }

    int c;
    while((c = fgetc(file)) != '\n' && c != EOF){}

    for (int i = 0; i < TABS_MAX_AMOUNT; i++) 
    {
        TL->tabs[i].isUsed = false;
        TL->tabs[i].name[0] = '\0';
        createTab(&(TL->tabs[i].tabHistory));
    }

    TL->count = tabCount;
    TL->currentIdx = activeIdx - 1;
    TL->tabCounter = 0;

    char tabData[1024];
    char tabUrl[20000];

    for (int i = 0; i < tabCount; i++) 
    {
        if(fgets(tabData, sizeof(tabData), file) == NULL) break;
        if(tabData[0] == '\0') break;

        char tabName[TAB_NAME_LENGTH];
        int historyCount = 0;
        int currentHistoryIdx = 0;

        if(sscanf(tabData, "%10s %d %d", tabName, &historyCount, &currentHistoryIdx) != 3) continue;

        strncpy(TL->tabs[i].name, tabName, TAB_NAME_LENGTH);
        TL->tabs[i].name[TAB_NAME_LENGTH - 1] = '\0';
        TL->tabs[i].isUsed = true;
        createTab(&(TL->tabs[i].tabHistory));

        int num = tabParser(TL->tabs[i].name);
        if(num > TL->tabCounter) TL->tabCounter = num;

        if(fgets(tabUrl, sizeof(tabUrl), file) == NULL) tabUrl[0] = '\0';
            
        Page *P = &(TL->tabs[i].tabHistory);
        createTab(P);

        if(historyCount == 0){
            P->Empty = true;
            continue;
        }

        char *urls[MAX_WEB];
        int got = 0;

        char *tok = strtok(tabUrl, " \t\r\n");

        while(got < historyCount){
            urls[got++] = tok;
            tok = strtok(NULL, " \t\r\n");
        }

        createStack(&(P->backHistory));
        for (int k = 0; k < currentHistoryIdx - 1; k++) 
        {
            Webname w;
            setWebname(&w, urls[k]);
            push(&(P->backHistory), w);
        }

        setWebname(&(P->currentTab), urls[currentHistoryIdx - 1]);
        P->Empty = false;

        createStack(&(P->forwardHistory));
        for (int k = historyCount - 1; k >= currentHistoryIdx; k--) 
        {
            Webname w;
            setWebname(&w, urls[k]);
            push(&(P->forwardHistory), w);
        }
    }

    if(TL->tabCounter == 0) TL->tabCounter = TL->count;

    if(PQ != NULL){
        int n = 0;
        if(fscanf(file, "%d", &n) == 1){
            if (n < 0) n = 0;
            if (n > HISTORY_MAX_AMOUNT) n = HISTORY_MAX_AMOUNT;

            CreateGlobalHistory(PQ);
            for (int i = 0; i < n; i++) 
            {
                char url[URL_MAX_LENGTH];
                int visited = 0;
                if (fscanf(file, "%255s %d", url, &visited) != 2) break;
                strncpy(PQ->buffer[i].url, url, URL_MAX_LENGTH - 1);
                PQ->buffer[i].url[URL_MAX_LENGTH - 1] = '\0';
                PQ->buffer[i].visited = visited;
                PQ->size = i + 1;
            }
        }
    }

    fclose(file);

    if(cacheMax != CACHE_MAX_AMOUNT || tabsMax != TABS_MAX_AMOUNT || downloadMax != DOWNLOAD_MAX_AMOUNT || maxPages != MAX_WEB_PAGES){
        printf("WARNING: config constants in %s differ from compiled limits. Using compiled limits.\n", f);
    }

    return true;
}

boolean SaveConfig(const TabsList *TL, const GlobalHistory *PQ, const char *folder){
    if(TL == NULL) return false;

    char path[512];
    strcpy(path, folder);
    strcat(path, "config.txt");

    FILE *check = fopen(path, "r");
    if(check){
        fclose(check);
        printf("WARNING: %s already exists, overwrite? (y/n): ", path);
        char ans;
        scanf(" %c", &ans);
        if (ans != 'y' && ans != 'Y') {
            printf("Save cancelled.\n");
            return false;
        }
        printf("Overwriting %s...\n", path);
        printf("Data saved!\n");
    } 
    else{
        printf("Saving data into %s...\n", path);
    }

    FILE *file = fopen(path, "w");
    if(!file){
        printf("ERROR: Could not open %s for writing.\n", path);
        return false;
    }

    fprintf(file, "%d %d %d %d\n", CACHE_MAX_AMOUNT, TABS_MAX_AMOUNT, DOWNLOAD_MAX_AMOUNT, MAX_WEB_PAGES);
    fprintf(file, "%d %d\n", TL->count, TL->currentIdx+1);

    for (int i = 0; i < TL->count; i++) 
    {
        const Page *P = &(TL->tabs[i].tabHistory);

        int backLen = length(P->backHistory);
        int forwardLen = length(P->forwardHistory);
        int historyCount = 0;
        int currentIdx = 0;

        if(P->Empty){
            historyCount = 0;
            currentIdx = 0;
        } 
        else{
            historyCount = backLen+forwardLen+1;
            currentIdx = backLen+1;
        }

        fprintf(file, "%s %d %d\n", TL->tabs[i].name, historyCount, currentIdx);

        if(historyCount == 0){
            fprintf(file, "\n");
            continue;
        }

        for (int k = 0; k <= P->backHistory.idxTop; k++) 
        {
            fprintf(file, "%s", P->backHistory.buffer[k].url);
            fprintf(file, " ");
        }

        fprintf(file, "%s", P->currentTab.url);

        for (int k = P->forwardHistory.idxTop; k >= 0; k--) 
        {
            fprintf(file, " %s", P->forwardHistory.buffer[k].url);
        }

        fprintf(file, "\n");
    }

    if(PQ != NULL){
        if(file != NULL){
            fprintf(file, "%d\n", PQ->size);
            for (int i = 0; i < PQ->size; i++)
            {
                fprintf(file, "%s %d\n", PQ->buffer[i].url, PQ->buffer[i].visited);
            }
        }
    }

    fclose(file);
    return true;
}