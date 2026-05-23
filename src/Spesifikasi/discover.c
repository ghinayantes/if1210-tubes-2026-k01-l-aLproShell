#include "../../header/discover.h"

unsigned int lcg(unsigned int current_seed) {
    unsigned int a = 1103515245;
    unsigned int c = 12345;
    unsigned int m = 2147483648; // 2^31
    return (a * current_seed + c) % m;
}

void runDiscover(WebPages *W, unsigned int *seed) {
    
    if (W->NEff < 5) {
        printf("[ERROR] Website yang tersedia kurang dari 5. Tidak bisa menjalankan Discover!\n");
        return;
    }

    printf("\n─────────── DISCOVER WEBSITES ───────────\n");
    unsigned int temp_seed = *seed;
    int count = 0;
    int picked[5] = {-1, -1, -1, -1, -1}; 

    while (count < 5) {
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
            printf("- %s\n", W->buffer[target_index].web_url);
            count++;
        }
    }
    
    *seed = temp_seed; // Simpan seed terakhir
    printf("─────────────────────────────────────────\n");
}