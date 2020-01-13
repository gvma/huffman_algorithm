#include "header/header.h"
#include "heap/heap.h"
#include "compressor/compressor.h"
#include "decompressor/decompressor.h"

FILE *get_file(char *file_path) {
    FILE *f = fopen(file_path, "rb");
    return f;
}

int main() {
    while (true) {
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
            compression(file, file_path);
            printf("\n");
            fclose(file);
        } else if (option == 2) {
            printf("Type the path of your file: \n");
            char file_path[1000];
            getchar();
            gets(file_path);
            FILE *compressed_file = get_file(file_path);
            if (compressed_file == NULL) {
                printf("There's no such file with the name %s!\n", file_path);
                continue;
            }
            printf("Opening %s!\n", file_path);
            FILE *decompressed_file = decompress(compressed_file, file_path);
            fclose(compressed_file);
            fclose(decompressed_file);
        }
    }
    getchar();
}