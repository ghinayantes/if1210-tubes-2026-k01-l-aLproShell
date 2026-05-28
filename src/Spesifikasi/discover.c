#include "../../header/discover.h"
#include <stdio.h>

unsigned int lcg(unsigned int current_seed) {
    unsigned int a = 1103515245;
    unsigned int c = 12345;
    unsigned int m = 2147483648;
    return (a * current_seed + c) % m;
}

void runDiscover(WebPages *W, unsigned int *seed) {
    printf("\n=== DISCOVER WEBSITES ===\n");
    
    int target_count = (W->NEff < 5) ? W->NEff : 5;
    
    if (target_count == 0) {
        printf("Database website kosong! Tidak ada halaman untuk di-discover.\n");
        printf("=========================\n\n");
        return;
    }

    unsigned int temp_seed = *seed;
    int count = 0;
    int picked[5] = {-1, -1, -1, -1, -1}; 

    while (count < target_count) {
        temp_seed = lcg(temp_seed);
        int target_index = temp_seed % (W->NEff); 
        
        int is_duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (picked[i] == target_index) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            picked[count] = target_index;
            printf("%d. ID: %d | URL: %s\n", count + 1, W->buffer[target_index].id, W->buffer[target_index].web_url);
            count++;
        }
    }
    
    *seed = temp_seed; 
    printf("=========================\n\n");
}