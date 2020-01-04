#include "hash.h"
#include "../header/header.h"

HASH_TABLE *create_hash_table() {
    HASH_TABLE *hash_table = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));
    int i, j;
    for (i = 0; i < 256; ++i) {
        for (j = 0; j < 3; ++j) {
            hash_table->new_mapping[i][j] = 0;
        }
    }
    return hash_table;
}

HASH_TABLE *generate_new_mapping(HUFF_NODE *root, FILE *compressed_file, int *trash_size) {
    HASH_TABLE *hash_table = create_hash_table();
    unsigned short mapping = 0;
    int compressed_length = 0;
    bytes_mapping(root, hash_table, compressed_file, mapping, compressed_length, trash_size);
    return hash_table;
}

void print_hash_table(HASH_TABLE *hash_table) {
    int i, j, k;
    for (i = 0; i < 256; ++i) {
        if (hash_table->new_mapping[i][0] != 0) {
            printf("=============================\n");
            printf("Character %c: ", (char)i);
            printf("Compressed Length: %d\n", hash_table->new_mapping[i][0]);
            printf("New Mapping: ");
            for (j = 0; j < 3; ++j) {
                printf("(");
                for (k = 8; k >= 0; --k) {
                    printf("%d", is_bit_i_set(hash_table->new_mapping[i][j], k));
                }
                printf("),");
            }
            printf("\n");
        }
    }
}