#include "saveload.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

boolean LoadFromCSV(WebPages *W, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) return false;

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
    return true;
}

boolean SaveToCSV(WebPages W, const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (!file) return false;

    for (int i = 0; i < W.NEff; i++) {
        fprintf(file, "%d,%s,%s\n", W.buffer[i].id, W.buffer[i].web_url, W.buffer[i].content);
    }
    fclose(file);
    return true;
}