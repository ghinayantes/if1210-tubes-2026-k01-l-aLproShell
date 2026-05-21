#include "saveload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

        for (int f = 0; f < 2 && valid; f++) {
            if(*p != ',' || *(p+1) != '"'){ 
                valid = false; 
                break; 
            }
            p += 2;

            int i = 0;
            while(*p){
                if(*p == '"'){
                    if(*(p+1) == '"'){        
                        if (i < size[f] - 1) data[f][i++] = '"';
                        p += 2;
                    } 
                    else{     
                        p++;
                        break;
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