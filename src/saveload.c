#include "saveload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LoadFromCSV(WebPages *W, char *f) {
    FILE *file = fopen(f, "r");
    if (!file) return;

    W->NEff = 0;
    char line[2000];

    while (fgets(line, sizeof(line), file)) {
        int id;
        char url[100];
        char content[1000];

        if (sscanf(line, "%d,\"%99[^\"]\",\"%999[^\"]\"", &id, url, content) == 3) {
            AddWeb(W, id, url, content);
        }
    }

    fclose(file);
}

void SaveToCSV(WebPages W, char *f) {
    FILE *file = fopen(f, "w");
    if (!file) return;

    for (int i = 0; i < W.NEff; i++) {
        fprintf(file, "%d,%s,%s\n", W.buffer[i].id, W.buffer[i].web_url, W.buffer[i].content);
    }
    fclose(file);
}