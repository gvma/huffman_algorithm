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
    unsigned char mapping = 0;
    int compressed_length = 0;
    bytes_mapping(root, hash_table, compressed_file, mapping, compressed_length, trash_size);
    return hash_table;
}

void print_hash_table(HASH_TABLE *hash_table) {
    int i, j, k;
    for (i = 0; i < 256; ++i) {
        printf("Character %c: ", (char)i);
        printf("Compressed Length: %d", hash_table->new_mapping[i][0]);
        for (j = 0; j < 3; ++j) {
            if (j) {
                printf("New Mapping: ");
                printf("(");
                for (k = 8; k >= 0; --k) {
                    printf("%d", is_bit_i_set(hash_table->new_mapping[i][j], k));
                }
                for (k = 8; k >= 0; --k) {
                    printf("%d", is_bit_i_set(hash_table->new_mapping[i][j], k));
                }
                printf("), Size: %d\n", hash_table->new_mapping[i][2]);
            }
        }
        printf("\n");
    }
}