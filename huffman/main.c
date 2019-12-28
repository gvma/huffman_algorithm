#include "header/header.h"
#include "heap/heap.h"
#include "compressor.h"

FILE *get_file(char *file_path) {
    FILE *f = fopen(file_path, "rb");
    return f;
}

int main() {
    while (1) {
        int option;
        printf("Select one option: \n");
        printf("(1) Compress\n");
        printf("(2) Decompress\n");
        printf("(3) Exit\n");
        scanf("%d", &option);
        if (option == 3) {
            return 0;
        }
        if (option == 1) {
            printf("Type the path of your file: \n");
            char file_path[1000];
            getchar();
            gets(file_path);
            FILE *file = get_file(file_path);
            if (file == NULL) {
                printf("There's no such file with the name %s!\n", file_path);
                continue;
            }
            printf("Opening %s!\nComposing frequency of bytes!\n", file_path);
            compress(file);
            printf("\n");
            fclose(file);
        }
    }
    getchar();
}